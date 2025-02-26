#ifndef THREAD_QUEUE_H_
#define THREAD_QUEUE_H_

// Thread queue node
struct node {
	struct node *next; // pointer to next node
	int *client_socket; // client socket id
};

// insert a socket into the queue
void enqueue(int *client_socket);

// Returns the pointer to a client_socket, if there is one.
// Otherwise returns NULL
int *dequeue();

#endif // THREAD_QUEUE_H_
