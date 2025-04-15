#ifndef CLIENT_HANDLE_H
#define CLIENT_HANDLE_H

// stuff for handling client connections - reads lines, echoes back
// and maybe prints them if verbose is on

// handle_client
// reads from client_socket till EOF/error. sends lines back to 
// client. if verbose_mode == 1, prints each line. closes socket
// when done
void handle_client(int client_socket, int verbose_mode);

#endif
