#ifndef SERVER_SETUP_H
#define SERVER_SETUP_H

// funcs for setting up and listening on TCP socket

// init server_socket 
// makes a socket, binds to port, and starts listening
// returns fd for the socket
// exits if anything goes wrong
int initialize_server_socket(int listen_port);

#endif
