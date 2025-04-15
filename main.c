#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
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

    // 1) parse cmd line args
    config = parse_arguments(argc, argv);

    // 2) setup server socket on the port
    listen_fd = initialize_server_socket(config.listen_port);

    printf("Server listening on port %d\n", config.listen_port);
    fflush(stdout);

    // 3) accept and handle connections one at a time
    while (1) {
        client_addr_len = sizeof(client_addr);
        client_fd = accept(listen_fd, (struct sockaddr *)&client_addr,
                           &client_addr_len);
        if (client_fd < 0) {
            perror("accept");
            close(listen_fd);
            exit(1);
        }

        // handle client till they disconnect
        handle_client(client_fd, config.verbose_mode);
    }

    // shouldn't ever get here normally
    close(listen_fd);
    return 0;
}
