#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "helpers/server_helper.h"
#include "server/server_game.h"


void parent_thread(int sockfd);
void server_thread(thread_args_t *args);


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
    pthread_t threads[MAX_PLAYER];

    for (int player_num = 0; player_num < MAX_PLAYER; player_num++) {
        // accept connections
        int accepted_sockfd = accept_connection(sockfd);

        thread_args_t args = { accepted_sockfd, player_num };

        pthread_create(&threads[player_num],
                       NULL,
                       (void *) server_thread,
                       (void *) &args);
    }

    parent_thread(sockfd);

    for (int i = 0; i < MAX_PLAYER; i++) {
        pthread_join(threads[i], NULL);
    }

    close(sockfd);
    return 0;
}


void parent_thread(int sockfd)
{
    // wait for two players to connect
    while (true) {
        if (is_connected[0] && is_connected[1]) {
            puts("both players connected");
            break;
        }
        usleep(10000);
    }

    init_server();

    // start game
    while (true) {
        if (is_connected[0] == false || is_connected[1] == false) {
            game_finish = true;
            break;
        }

        update_ball_pos();

        usleep(6000);
        // usleep(1000000);
    }
}


void server_thread(thread_args_t *args)
{
    int accepted_sockfd = args->accepted_sockfd;
    int player_num      = args->player_num;
    int op_player_num   = (player_num + 1) % MAX_PLAYER;

    printf("player %d connected\n", player_num);
    is_connected[player_num] = true;


    while (is_connected[player_num] && !game_finish) {
        // receive data from client
        to_server_t to_server = receive_data(accepted_sockfd);
        if (player_num == 1) {
            reverse_paddle_pos(&to_server.paddle_pos);
        }
        paddle_pos[player_num]   = to_server.paddle_pos;
        is_connected[player_num] = to_server.is_connected;

        // send data to client
        ball_t tmp_ball_pos = ball_pos;
        if (player_num == 1) {
            reverse_ball_pos(&tmp_ball_pos);
        }
        paddle_t tmp_paddle_pos = paddle_pos[op_player_num];
        if (player_num == 1) {
            reverse_paddle_pos(&tmp_paddle_pos);
        }
        to_client_t to_client = (to_client_t){
            .round           = round_num,
            .ball_pos        = tmp_ball_pos,
            .op_paddle_pos   = tmp_paddle_pos,
            .op_is_connected = is_connected[op_player_num],
        };
        send_data(accepted_sockfd, &to_client);

        usleep(30000);
        // printf("player %d\n", player_num);
    }

    printf("player %d disconnected\n", player_num);

    close(accepted_sockfd);
}
