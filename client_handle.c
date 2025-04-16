#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include "client_handle.h"
#include "sync_helper.h"

// we read from socket till client disconnects
// using small buffer to look for '\n'
// then echo line back to client (with the '\n')

void handle_client(int client_socket, int verbose_mode)
{
    char buffer[1024];
    int bytes_read;
    int i;

    // read from client socket chunk by chunk
    // and check for newlines
    int line_start = 0;       // where current line starts in buffer
    int total_in_buffer = 0;  // how many bytes in buffer rn

    while (1) {
        bytes_read = recv(client_socket, buffer + total_in_buffer,
                          (int)(sizeof(buffer) - 1 - total_in_buffer), 0);

        if (bytes_read <= 0) {
            // client closed or error happened
            break;
        }

        total_in_buffer += bytes_read;
        buffer[total_in_buffer] = '\0'; // null-terminate for safety

        // process complete lines in buffer
        for (i = 0; i < total_in_buffer; i++) {
            if (buffer[i] == '\n') {
                // found newline = complete line from line_start to i
                int line_length = i - line_start + 1; // include newline

                // echo back to client
                send(client_socket, &buffer[line_start], line_length, 0);

                // print to console if verbose on
                if (verbose_mode) {
                    // use mutex to prevent output interleaving
                    pthread_mutex_lock(&console_mutex);
                    
                    // temp null-terminate for printing
                    char saved_char = buffer[i + 1];
                    buffer[i + 1] = '\0';
                    fprintf(stdout, "%s", &buffer[line_start]);
                    fflush(stdout);
                    buffer[i + 1] = saved_char; // put it back
                    
                    pthread_mutex_unlock(&console_mutex);
                }

                line_start = i + 1;
            }
        }

        // move leftover partial line to start of buffer
        if (line_start > 0 && line_start < total_in_buffer) {
            memmove(buffer, &buffer[line_start], total_in_buffer - line_start);
            total_in_buffer -= line_start;
            line_start = 0;
        } else if (line_start == total_in_buffer) {
            // all processed, reset everything
            total_in_buffer = 0;
            line_start = 0;
        }
    }

    close(client_socket);
}

// thread function that handles a client connection
void *client_thread(void *arg)
{
    client_args_t *args = (client_args_t *)arg;
    
    // handle the client using our existing function
    handle_client(args->client_socket, args->verbose_mode);
    
    // free the args that were malloc'd in main
    free(args);
    return NULL;
}
