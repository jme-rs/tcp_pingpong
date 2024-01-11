#ifndef SERVER_HELPER_H_
#define SERVER_HELPER_H_


#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_CLIENTS 2


typedef struct {
    int accepted_sockfd;
    int player_num;
} thread_args_t;


void check_args(int argc, char *argv[]);
int  get_socket();
void bind_socket(int sockfd, int port);
int  accept_connection(int sockfd);


#endif // SERVER_HELPER_H_
