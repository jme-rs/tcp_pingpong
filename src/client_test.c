#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#include "client/client_game.h"


int main()
{
    init_ncurses();
    init_client();

    while (true) {
        int ch = getch();
        if (ch == 'q')
            break;

        clear();
        draw_field();
        draw_paddle();
        draw_ball();
        refresh();
    }

    finish_ncurses();
}
