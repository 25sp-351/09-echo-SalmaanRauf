#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse_args.h"

#define DEFAULT_PORT 2345

static void print_usage_and_exit(void)
{
    // show how to use and exit
    fprintf(stderr, "Usage: echo_server [-p port] [-v]\n");
    exit(1);
}

server_config_t parse_arguments(int argc, char *argv[])
{
    server_config_t config;
    int ix;

    // default settings
    config.listen_port = DEFAULT_PORT;
    config.verbose_mode = 0;

    // go thru args
    ix = 1; // skip program name
    while (ix < argc) {
        // check for -p
        if (strcmp(argv[ix], "-p") == 0) {
            ix++;
            if (ix >= argc) {
                // -p was last arg = missing port num
                print_usage_and_exit();
            }
            // convert to int
            config.listen_port = atoi(argv[ix]);
            if (config.listen_port <= 0) {
                // bad port
                fprintf(stderr, "Invalid port '%s'\n", argv[ix]);
                print_usage_and_exit();
            }
        }
        else if (strcmp(argv[ix], "-v") == 0) {
            config.verbose_mode = 1;
        }
        else {
            // unknown arg
            print_usage_and_exit();
        }
        ix++;
    }
    return config;
}
