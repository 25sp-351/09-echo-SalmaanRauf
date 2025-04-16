#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

// stuff for parsing cmd line args

typedef struct {
    int listen_port;     // TCP port to listen on
    int verbose_mode;    // 1 if -v was used, 0 otherwise
} server_config_t;

// parse_arguments
// parses cmd line args. -p changes port, -v enables verbose which just prints it out in our console
// prints usage and exits if args are bad
// argc, argv: from main
server_config_t parse_arguments(int argc, char *argv[]);

#endif
