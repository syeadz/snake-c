#include "tui.h"

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0); 

    return local_win;
}

WINDOW *init_game_win()
{
    return create_newwin(LINES, COLS, 0, 0);
}