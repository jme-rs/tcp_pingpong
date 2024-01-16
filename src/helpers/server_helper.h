#ifndef SERVER_HELPER_H
#define SERVER_HELPER_H


#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../include/types.h"


typedef struct {
    int accepted_sockfd;
    int player_num;
} thread_args_t;


void        check_args(int argc, char *argv[]);
int         get_socket();
void        bind_socket(int sockfd, int port);
int         accept_connection(int sockfd);
to_server_t receive_data(int sockfd);
void        send_data(int sockfd, to_client_t *data);


#endif // SERVER_HELPER_H
