#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "helpers/server_helper.h"


void server_thread(thread_args_t *args);


pthread_mutex_t mutex;


// server entry point
int main(int argc, char *argv[])
{
    // check arguments
    check_args(argc, argv);

    // create socket
    int sockfd = get_socket();

    // bind socket
    int port = atoi(argv[1]);
    bind_socket(sockfd, port);

    // listen for connections
    listen(sockfd, 5);
    printf("Server listening on port %d...\n", port);

    // create threads
    pthread_t threads[MAX_CLIENTS];
    pthread_mutex_init(&mutex, NULL);

    for (int player_num = 0; player_num < MAX_CLIENTS; player_num++) {
        // accept connections
        int accepted_sockfd = accept_connection(sockfd);

        thread_args_t args = { accepted_sockfd, player_num };

        pthread_create(&threads[player_num],
                       NULL,
                       (void *) server_thread,
                       (void *) &args);
    }

    for (int i = 0; i < MAX_CLIENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    close(sockfd);
    return 0;
}


void server_thread(thread_args_t *args)
{
    char buffer[BUFSIZ];
    int  n;
    int  player_num      = args->player_num;
    int  accepted_sockfd = args->accepted_sockfd;

    printf("connected player %d\n", player_num);

    // event loop
    while (true) {
        memset(buffer, 0, BUFSIZ);
        n = recv(accepted_sockfd, buffer, BUFSIZ, 0);
        if (n < 0) {
            perror("recv");
            exit(EXIT_FAILURE);
        }

        if (strncmp(buffer, "exit\n", 5) == 0) {
            printf("disconnected player %d\n", player_num);
            break;
        }

        printf("player %d: %s", player_num, buffer);

        n = send(accepted_sockfd, buffer, strlen(buffer), 0);
        if (n < 0) {
            perror("send");
            exit(EXIT_FAILURE);
        }
    }

    close(accepted_sockfd);
}
