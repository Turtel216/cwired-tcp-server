#include "thread_queue.h"
#include <stdlib.h>

// Pointers for head and tail of queue data structure
static struct node *head = NULL;
static struct node *tail = NULL;

// insert a socket into the queue
void enqueue(int *client_socket)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->client_socket = client_socket;
	new_node->next = NULL;

	if (tail == NULL) {
		head = new_node;
	} else {
		tail->next = new_node;
	}

	tail = new_node;
}

// Returns the pointer to a client_socket, if there is one.
// Otherwise returns NULL
int *dequeue()
{
	if (head == NULL) {
		return NULL;
	}

	int *result = head->client_socket;
	struct node *temp = head;
	head = head->next;
	if (head == NULL) {
		tail = NULL;
	}
	free(temp);
	return result;
}
