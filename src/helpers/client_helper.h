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


void check_args(int argc, char *argv[]);
int  get_socket();
void create_connection(int sockfd, char *host, int port);


#endif // CLIENT_HELPER_H_
