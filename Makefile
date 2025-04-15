CFLAGS = -Wall -g
CC = clang

# final program and the .o files
all: echo_server

echo_server: main.o parse_args.o server_setup.o client_handle.o
	$(CC) $(CFLAGS) -o echo_server main.o parse_args.o server_setup.o client_handle.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o echo_server
