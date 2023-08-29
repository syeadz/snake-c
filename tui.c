#include "tui.h"

/**
 * Creates a new window based on parameters.
 */
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);

    return local_win;
}

WINDOW *init_game_win()
{
    return create_newwin(LINES - 2, COLS, 2, 0);
}

WINDOW *init_info_win()
{
    return create_newwin(3, COLS, 0, 0);
}

// void print_centered(WINDOW *win, char str[]) {
//     int length = 
// }