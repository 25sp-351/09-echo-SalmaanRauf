#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server_setup.h"

int initialize_server_socket(int listen_port)
{
    int sock_fd;
    int opt_val;
    struct sockaddr_in server_addr;

    // make a TCP socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        exit(1);
    }

    // let us reuse local addrs
    opt_val = 1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val)) < 0) {
        perror("setsockopt");
        close(sock_fd);
        exit(1);
    }

    // zero out server_addr and fill it in
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(listen_port);

    // bind socket to our port
    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(sock_fd);
        exit(1);
    }

    // start listening
    if (listen(sock_fd, 5) < 0) {
        perror("listen");
        close(sock_fd);
        exit(1);
    }

    return sock_fd;
}
