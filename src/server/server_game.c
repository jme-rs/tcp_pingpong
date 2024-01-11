#include "server_game.h"


void init_server() {
    round_num = 1;
    ball_pos = (ball_t) { .x = MAX_X / 2, .y = MAX_Y / 2, .angle = M_PI / 4 };
    game_finish = false;
}

void update_ball_pos() {
    // paddle_t player0 = paddle_pos[0];
    // paddle_t player1 = paddle_pos[1];

    ball_t ball = ball_pos;
    ball.x += BALL_SPEED * cos(ball.angle);
    ball.y += BALL_SPEED * sin(ball.angle);

    if (ball.x < 1) {
        ball.x = 1;
        ball.angle = M_PI - ball.angle;
    } else if (MAX_X - 1 < ball.x) {
        ball.x = MAX_X - 1;
        ball.angle = M_PI - ball.angle;
    }

    if (ball.y < BOUNDARY_HEIGHT) {
        ball.y = BOUNDARY_HEIGHT;
        ball.angle = -ball.angle;
    } else if (MAX_Y - BOUNDARY_HEIGHT < ball.y) {
        ball.y = MAX_Y - BOUNDARY_HEIGHT;
        ball.angle = -ball.angle;
    }

    ball_pos = ball;
    printf("ball_pos: %f, %f\n", ball.x, ball.y);
}