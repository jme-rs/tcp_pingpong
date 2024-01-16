#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H


#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/types.h"


// shared resources
ball_t     ball_pos;
paddle_t   my_paddle_pos;
paddle_t   op_paddle_pos;
round_t    round_num;
quitflag_t is_connected;
quitflag_t op_is_connected;
quitflag_t game_finish;

void init_ncurses();
void finish_ncurses();
void init_client();
void draw_field();
void draw_paddle();
void draw_ball();
void wait_for_opponent();


#endif // CLIENT_GAME_H
