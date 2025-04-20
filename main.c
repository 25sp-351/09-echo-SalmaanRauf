#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "parse_args.h"
#include "server_setup.h"
#include "client_handle.h"

int main(int argc, char *argv[])
{
    int listen_fd;
    int client_fd;
    server_config_t config;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    pthread_t tid;

    // 1) parse cmd line args
    config = parse_arguments(argc, argv);

    // 2) setup server socket on the port
    listen_fd = initialize_server_socket(config.listen_port);

    printf("Server listening on port %d\n", config.listen_port);
    fflush(stdout);

    // 3) accept and handle connections with threads
    while (1) {
        client_addr_len = sizeof(client_addr);
        client_fd = accept(listen_fd, (struct sockaddr *)&client_addr,
                           &client_addr_len);
        if (client_fd < 0) {
            perror("accept");
            continue;  // keep server alive
        }

        // package args for the worker thread
        client_args_t *args = malloc(sizeof(client_args_t));
        if (!args) {
            perror("malloc");
            close(client_fd);
            continue;
        }
        args->client_socket = client_fd;
        args->verbose_mode = config.verbose_mode;

        // create a thread to handle this client
        if (pthread_create(&tid, NULL, client_thread, args) != 0) {
            perror("pthread_create");
            close(client_fd);
            free(args);
            continue;
        }
        
        // detach thread so its resources are freed when it exits
        pthread_detach(tid);
    }

    // shouldn't ever get here normally
    close(listen_fd);
    return 0;
}
