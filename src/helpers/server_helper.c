#include "server_helper.h"


void check_args(int argc, char *_argv[])
{
    if (argc != 2) {
        printf("Usage: ./prog port\n");
        exit(EXIT_FAILURE);
    }
}


int get_socket()
{
    int sockfd;

    if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    return sockfd;
}


void bind_socket(int sockfd, int port)
{
    struct sockaddr_in serv_addr;

    memset((char *) &serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port        = htons(port);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
}


int accept_connection(int sockfd)
{
    struct sockaddr_in cli_addr;

    int clilen = sizeof(cli_addr);
    int accepted_sockfd
        = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

    if (accepted_sockfd < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    return accepted_sockfd;
}


to_server_t receive_data(int sockfd)
{
    to_server_t data;
    int         n = recv(sockfd, &data, sizeof(to_server_t), 0);

    if (n < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    return data;
}


void send_data(int sockfd, to_client_t *data)
{
    int n = send(sockfd, data, sizeof(to_client_t), 0);

    if (n < 0) {
        perror("write");
        exit(EXIT_FAILURE);
    }
}