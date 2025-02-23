#ifndef SERVER_H_
#define SERVER_H_

// handle_connection handles an incomming connection from a given `client_socket`
void *handle_connection(void *client_socket);

#endif // SERVER_H_
