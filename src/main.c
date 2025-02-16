#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(8080);
	bind(server_fd, (struct sockaddr *)&address, sizeof(address));

	listen(server_fd, 3);

	printf("Server is running and listening on port 8080...\n");

	while (1) {
		int addrlen = sizeof(address);
		int new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t *)&addrlen);

		if (new_socket < 0) {
			perror("Failed to accept connection");
			continue;
		}

		printf("Connection accepted.\n");

		char buffer[1024] = { 0 };
		read(new_socket, buffer, 1024);
		printf("Client message: %s\n", buffer);

		// Respond to the client
		char *response = "Hello from server!";
		write(new_socket, response, strlen(response));

		close(new_socket);
		printf("Connection closed.\n");
	}

	close(server_fd);

	return 0;
}
