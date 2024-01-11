#include "client_game.h"


void init_ncurses()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(REPORT_MOUSE_POSITION, NULL);
    printf("\033[?1003h\n");
    curs_set(0);
    timeout(30);
}


void finish_ncurses()
{
    printf("\033[?1003l\n");
    endwin();
}


void init_client()
{
    ball_pos      = (ball_t){ .x = MAX_X / 2, .y = MAX_Y / 2, .angle = M_PI / 4 };
    my_paddle_pos = MAX_X / 2;
    op_paddle_pos = MAX_X / 2;
}


void draw_field()
{
    // horizontal lines
    for (int x = 0; x < MAX_X; x++) {
        mvaddch(BOUNDARY_HEIGHT - 1, x, '-');
        mvaddch(MAX_Y - BOUNDARY_HEIGHT, x, '-');
    }

    // vertical lines
    for (int y = 0; y < MAX_Y; y++) {
        mvaddch(y, 0, '|');
        mvaddch(y, MAX_X - 1, '|');
    }
}


void draw_paddle()
{
    MEVENT e;
    paddle_t pos_x;
    if (getmouse(&e) == OK)
        pos_x = e.x;
    else
        pos_x = my_paddle_pos;

    // my paddle
    if (pos_x < PADDLE_WIDTH / 2 + 1)
        pos_x = PADDLE_WIDTH / 2 + 1;
    else if (MAX_X - PADDLE_WIDTH / 2 + 1 < pos_x)
        pos_x = MAX_X - PADDLE_WIDTH / 2 + 1;

    my_paddle_pos = pos_x;

    for (int x = -PADDLE_WIDTH / 2; x < PADDLE_WIDTH / 2 + 1; x++)
        mvaddch(MAX_Y - PADDLE_POS_Y, my_paddle_pos + x, '-');

    // opponent's paddle
    for (int x = -PADDLE_WIDTH / 2; x < PADDLE_WIDTH / 2 + 1; x++)
        mvaddch(PADDLE_POS_Y - 1, op_paddle_pos + x, '-');
}

void draw_ball()
{
    // clear
    mvaddch(ball_pos.y, ball_pos.x, ' ');

    // move
    ball_pos.x += BALL_SPEED * cos(ball_pos.angle);
    ball_pos.y += BALL_SPEED * sin(ball_pos.angle);

    // bounce
    if (ball_pos.x < 1 || MAX_X - 1 < ball_pos.x)
        ball_pos.angle = M_PI - ball_pos.angle;
    else if (ball_pos.y < BOUNDARY_HEIGHT || MAX_Y - BOUNDARY_HEIGHT < ball_pos.y)
        ball_pos.angle = -ball_pos.angle;

    // draw
    mvaddch(ball_pos.y, ball_pos.x, 'o');
}