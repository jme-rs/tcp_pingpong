#ifndef CLIENT_HELPER_H_
#define CLIENT_HELPER_H_


#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../include/types.h"


void        check_args(int argc, char *argv[]);
int         get_socket();
void        create_connection(int sockfd, char *host, int port);
to_client_t receive_data(int sockfd);
void        send_data(int sockfd, to_server_t *data);


#endif // CLIENT_HELPER_H_
