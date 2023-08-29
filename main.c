#include <time.h>
#include <stdlib.h>

#include "logic.h"
#include "linked_list.h"
#include "tui.h"

int main()
{
    // Setup
    srand(time(NULL));
    initscr();
    curs_set(0);
    noecho();
    WINDOW *win = init_game_win();
    State state = {.ate = false, .died = false, .points = 0};

    Snake snake = {.body = init_list(LINES / 2, COLS / 2), .dir = Up};
    move_snake(win, &state, &snake);
    spawn_food(win);
    wrefresh(win);

    char input;
    while (input != 'q')
    {
        input = wgetch(win);
        set_dir(&snake, input);
        move_snake(win, &state, &snake);
        if (state.died == true)
        {
            mvwaddstr(win, LINES / 2, COLS / 2, "YOU HAVE DIED");
        }
        else if (state.ate) {
            state.ate = false;
            spawn_food(win);
        }
        wrefresh(win);
    }

    // End
    endwin();
    return 0;
}