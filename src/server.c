#include "server.h"
#include "error.h"
#include <linux/limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 4096

// handle_connection handles an incomming connection from a given `client_socket`
void handle_connection(int client_socket)
{
	char buffer[BUFSIZE];
	size_t bytes_read;
	int msg_size = 0;
	char actual_path[PATH_MAX + 1];

	// read incomming message
	while ((bytes_read = read(client_socket, buffer + msg_size,
				  sizeof(buffer) - msg_size - 1)) > 0) {
		msg_size += bytes_read;
		if (msg_size > BUFSIZE - 1 || buffer[msg_size - 1] == '\n')
			break;

		check_err(bytes_read, "recv error");
		buffer[msg_size - 1] = 0; // null terminate the message

		printf("REQUEST: %s\n", buffer);
		fflush(stdout);

		if (realpath(buffer, actual_path) == NULL) {
			printf("ERROR, bad path: %s\n", buffer);
			close(client_socket);
			return;
		}

		FILE *fp = fopen(actual_path, "r");
		if (fp == NULL) {
			printf("ERROR, open: %s\n", buffer);
			close(client_socket);
			return;
		}

		// Very insecure. TODO limit client to certain files
		while ((bytes_read = fread(buffer, 1, BUFSIZE, fp)) > 0) {
			printf("sending %zu bytes\n", bytes_read);
			write(client_socket, buffer, bytes_read);
		}

		close(client_socket);
		fclose(fp);
		printf("closing connection\n");
	}
}
