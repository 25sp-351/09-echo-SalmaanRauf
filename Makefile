CFLAGS = -Wall -g -pthread
CC = clang

# final program and the .o files
all: echo_server

echo_server: main.o parse_args.o server_setup.o client_handle.o sync_helper.o
	$(CC) $(CFLAGS) -o echo_server main.o parse_args.o server_setup.o client_handle.o sync_helper.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o echo_server
