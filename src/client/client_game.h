#ifndef GAME_H_
#define GAME_H_


#include <ncurses.h>
#include <stdio.h>

#ifndef __USE_MISC
#define __USE_MISC
#endif
#include <math.h>

#include "include/types.h"


// shared resources
ball_t   ball_pos;
paddle_t my_paddle_pos;
paddle_t op_paddle_pos;

void init_ncurses();
void finish_ncurses();
void init_client();
void draw_field();
void draw_paddle();
void draw_ball();


#endif // GAME_H_
