#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdbit.h>
#include <stdio.h>
#include <pthread.h>
#include "./error.h"
#include "./server.h"
#include "./thread_queue.h"

// Config Macros
#define SERVER_PORT 8080
#define SERVER_BACKLOG 100
#define THREAD_POOL_SIZE 20

// GLOBAL VARIABLES
// thread pool for handling connections
static pthread_t thread_pool[THREAD_POOL_SIZE];
// mutex for controlling access to thread_queue
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// FUNCTION DEFINITIONS
// Handle a connection inside the thread pool
static void *pool_handler(void *arg);

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

int main(int argc, char **argv)
{
	int server_socket, client_socket, addr_size;
	SA_IN server_addr, client_addr;

	for (size_t i = 0; i < THREAD_POOL_SIZE; ++i) {
		pthread_create(&thread_pool[i], NULL, pool_handler, NULL);
	}

	check_err((server_socket = socket(AF_INET, SOCK_STREAM, 0)),
		  "Failed to create socket");

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(SERVER_PORT);

	check_err(bind(server_socket, (SA *)&server_addr, sizeof(server_addr)),
		  "Bind Failed");
	check_err(listen(server_socket, SERVER_BACKLOG), "Listen Failed");

	while (true) {
		printf("Waiting for connections\n");

		addr_size = sizeof(SA_IN);
		check_err(client_socket = accept(server_socket,
						 (SA *)&client_addr,
						 (socklen_t *)&addr_size),
			  "Accept Failed");
		printf("Connected\n");

		// Spawn new thread to handle connection
		int *pclient = malloc(sizeof(int));
		*pclient = client_socket;

		// Add to thread pool queue
		pthread_mutex_lock(&mutex);
		enqueue(pclient);
		pthread_mutex_unlock(&mutex);
	}

	return EXIT_SUCCESS;
}

// Handle a connection inside the thread pool
static void *pool_handler(void *arg)
{
	while (true) {
		// Remove from thread pool queue
		pthread_mutex_lock(&mutex);
		int *pclient = dequeue();
		pthread_mutex_unlock(&mutex);

		if (pclient != NULL) {
			handle_connection(pclient);
		}
	}
}
