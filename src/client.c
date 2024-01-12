#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "client/client_game.h"
#include "helpers/client_helper.h"


void process();
void client_thread(int *sockfd);


// client entry point
int main(int argc, char *argv[])
{
    check_args(argc, argv);

    int sockfd = get_socket();
    int port   = strtol(argv[2], NULL, 10);
    create_connection(sockfd, argv[1], port);

    pthread_t thread;
    pthread_create(&thread, NULL, (void *) client_thread, (void *) &sockfd);

    process(sockfd);

    pthread_join(thread, NULL);
    close(sockfd);
    return 0;
}


void process()
{
    printf("Connected!\n");
    is_connected = true;

    init_ncurses();
    init_client();

    wait_for_opponent();

    while (true) {
        int ch = getch();
        if (ch == 'q') {
            is_connected = false;
            break;
        }

        if (!op_is_connected) {
            is_connected = false;
            clear();
            mvprintw(0, 0, "Opponent disconnected!");
            refresh();
            sleep(2);
            break;
        }

        clear();
        draw_field();
        draw_paddle();
        draw_ball();
        refresh();
    }

    finish_ncurses();
}


void client_thread(int *sockfd)
{
    while (!is_connected)
        usleep(10000);

    while (is_connected) {
        to_server_t to_server = (to_server_t){
            .paddle_pos   = my_paddle_pos,
            .is_connected = is_connected,
        };
        send_data(*sockfd, &to_server);

        to_client_t to_client = receive_data(*sockfd);
        round_num             = to_client.round;
        ball_pos              = to_client.ball_pos;
        op_paddle_pos         = to_client.op_paddle_pos;
        op_is_connected       = to_client.op_is_connected;

        usleep(30000);
    }

    // finalize
    to_server_t to_server = (to_server_t){
        .paddle_pos   = my_paddle_pos,
        .is_connected = is_connected,
    };
    send_data(*sockfd, &to_server);

    to_client_t to_client = receive_data(*sockfd);
    round_num             = to_client.round;
    ball_pos              = to_client.ball_pos;
    op_paddle_pos         = to_client.op_paddle_pos;
    op_is_connected       = to_client.op_is_connected;

    puts("Disconnected!");
}
