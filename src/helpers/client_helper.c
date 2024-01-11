#include "client_helper.h"


void check_args(int argc, char *_argv[])
{
    if (argc != 3) {
        printf("Usage: ./prog host port\n");
        exit(1);
    }
}


int get_socket()
{
    int sockfd;

    if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket");
        exit(1);
    }

    return sockfd;
}


void create_connection(int sockfd, char *host, int port)
{
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));

    serv.sin_family = PF_INET;
    serv.sin_port   = htons(port);

    printf("Connecting to %s:%d\n", host, port);

    inet_aton(host, &serv.sin_addr);
    if (connect(sockfd, (struct sockaddr *) &serv, sizeof(serv)) < 0) {
        perror("connect");
        exit(1);
    }
}


to_client_t receive_data(int sockfd)
{
    to_client_t data;
    int         n = recv(sockfd, &data, sizeof(data), 0);

    if (n < 0) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    return data;
}


void send_data(int sockfd, to_server_t *data) {
    int n = send(sockfd, data, sizeof(*data), 0);

    if (n < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    }
}