#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers/client_helper.h"


void process(int sockfd);


// client entry point
int main(int argc, char *argv[])
{
    check_args(argc, argv);

    int sockfd = get_socket();
    int port   = strtol(argv[2], NULL, 10);
    create_connection(sockfd, argv[1], port);
    process(sockfd);
    close(sockfd);

    return 0;
}


void process(int sockfd)
{
    char buf[BUFSIZ];

    printf("Connected!\n");

    while (true) {
        printf("==> ");
        if (fgets(buf, BUFSIZ, stdin) < 0) {
            perror("fgets");
            break;
        }

        int len = send(sockfd, buf, strlen(buf), 0);
        if (strncasecmp(buf, "exit\n", 5) == 0) {
            break;
        }

        len      = recv(sockfd, buf, len, 0);
        buf[len] = '\0';
        printf("<== %s\n", buf);
    }
}
