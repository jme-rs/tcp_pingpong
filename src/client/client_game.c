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
    is_connected  = true;
    ball_pos      = (ball_t){ .x = MAX_X / 2, .y = MAX_Y / 2, .angle = 0.0 };
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
    MEVENT   e;
    paddle_t pos_x;
    if (getmouse(&e) == OK)
        pos_x = e.x;
    else
        pos_x = my_paddle_pos;

    // my paddle
    if (pos_x < PADDLE_WIDTH / 2 + 1)
        pos_x = PADDLE_WIDTH / 2 + 1;
    else if (MAX_X - PADDLE_WIDTH / 2 - 2 < pos_x)
        pos_x = MAX_X - PADDLE_WIDTH / 2 - 2;

    my_paddle_pos = pos_x;

    for (int x = -PADDLE_WIDTH / 2; x < PADDLE_WIDTH / 2 + 1; x++)
        mvaddch(MAX_Y - PADDLE_POS_Y - 1, my_paddle_pos + x, '-');

    // opponent's paddle
    for (int x = -PADDLE_WIDTH / 2; x < PADDLE_WIDTH / 2 + 1; x++)
        mvaddch(PADDLE_POS_Y, op_paddle_pos + x, '-');

    mvprintw(1, 0, "op_paddle_pos: %d", op_paddle_pos);
    mvprintw(MAX_Y - 1, 0, "my_paddle_pos: %d", my_paddle_pos);
}


void draw_ball()
{
    mvaddch(ball_pos.y, ball_pos.x, 'o');
    mvprintw(0, 0, "(x, y): (%f, %f)", ball_pos.x, ball_pos.y);
}


void wait_for_opponent()
{
    mvprintw(0, 0, "Waiting for opponent...");
    refresh();
    while (!op_is_connected)
        usleep(300);
}
