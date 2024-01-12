#include "server_game.h"


void init_server()
{
    round_num   = 1;
    ball_pos    = (ball_t){ .x = MAX_X / 2, .y = MAX_Y / 2, .angle = M_PI / 2 };
    game_finish = false;
}

void update_ball_pos()
{
    // ball_pos = (ball_t){ .x = 1.0, .y = 10.0, .angle = 0.0 };

    paddle_t player0_pos = paddle_pos[0];
    paddle_t player1_pos = paddle_pos[1];

    ball_t ball = ball_pos;
    ball.x += BALL_SPEED * cos(ball.angle);
    ball.y += BALL_SPEED * sin(ball.angle);

    // wall reflection
    if (ball.x < 1) {
        ball.x     = 1;
        ball.angle = M_PI - ball.angle;
    }
    else if (MAX_X - 1 < ball.x) {
        ball.x     = MAX_X - 1;
        ball.angle = M_PI - ball.angle;
    }

    if (ball.y < BOUNDARY_HEIGHT) {
        ball.y     = BOUNDARY_HEIGHT;
        ball.angle = -ball.angle;
    }
    if (MAX_Y - BOUNDARY_HEIGHT < ball.y) {
        ball.y     = MAX_Y - BOUNDARY_HEIGHT;
        ball.angle = -ball.angle;
    }

    // paddle reflection
    if (MAX_Y - PADDLE_POS_Y - 1 == (int) ball.y
        && player0_pos - PADDLE_WIDTH / 2 - 1 < ball.x
        && ball.x < player0_pos + PADDLE_WIDTH / 2 + 1) {
        ball.angle = -ball.angle;
    }
    if (PADDLE_POS_Y == (int) ball.y
        && player1_pos - PADDLE_WIDTH / 2 - 1 < ball.x
        && ball.x < player1_pos + PADDLE_WIDTH / 2 + 1) {
        ball.angle = -ball.angle;
    }

    ball_pos = ball;
    // printf("ball_pos: %f, %f\n", ball.x, ball.y);
}


void reverse_ball_pos(ball_t *ball)
{
    ball->x = MAX_X - ball->x - 1;
    ball->y = MAX_Y - ball->y;
}


void reverse_paddle_pos(paddle_t *paddle)
{
    *paddle = MAX_X - *paddle - 1;
}
