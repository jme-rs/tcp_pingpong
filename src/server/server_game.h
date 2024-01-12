#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_


#include <stdio.h>

#ifndef __USE_MISC
#define __USE_MISC
#endif
#include <math.h>

#include "../include/types.h"

#define MAX_PLAYER 2


quitflag_t is_connected[MAX_PLAYER];
ball_t     ball_pos;
paddle_t   paddle_pos[MAX_PLAYER];
round_t    round_num;
quitflag_t game_finish;

void init_server();
void update_ball_pos();
void reverse_ball_pos(ball_t *ball);
void reverse_paddle_pos(paddle_t *paddle);


#endif // SERVER_GAME_H_