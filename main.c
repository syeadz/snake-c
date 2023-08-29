#include <time.h>
#include <stdlib.h>

#include "logic.h"
#include "linked_list.h"
#include "tui.h"

// This is basically the game speed
#define TIMEOUTX 50
#define TIMEOUTY 90

int main()
{
    // For randomization
    srand(time(NULL));

    // Setup
    // ncurses options
    initscr();
    curs_set(0);
    noecho();

    // initialization of game
    WINDOW *win = init_game_win();
    GameState state = {.ate = false, .died = false, .points = 0};
    Snake snake = {.body = init_list(LINES / 2, COLS / 2), .dir = Up};
    move_snake(win, &state, &snake);
    spawn_food(win);
    wrefresh(win);

    // Game loopo
    char input = '@';
    char old_input = 'X';
    while (input != 'q')
    {
        // Timeout will depend on direction moving, X is set faster because Y is 
        // naturally faster
        Dir cur_dir = snake.dir;
        if (cur_dir == Up || cur_dir == Down)
        {
            wtimeout(win, TIMEOUTY);
        }
        else
        {
            wtimeout(win, TIMEOUTX);
        }

        // Check game state and respond accordingly
        if (state.died == true)
        {
            mvwaddstr(win, LINES / 2, COLS / 2, "YOU HAVE DIED");
        }
        else if (state.ate)
        {
            state.ate = false;
            spawn_food(win);
        }

        // wgetch will timeout if nothing is pressed, returning an ERR
        old_input = input;
        input = wgetch(win);

        if (input == ERR)
        {
            move_snake(win, &state, &snake);
            wrefresh(win);
            continue;
        }
        else if (input == old_input) // Temporary fix for pressed down key
        {
            continue;
        }

        set_dir(&snake, input);
        move_snake(win, &state, &snake);

        wrefresh(win);
    }

    // End
    endwin();
    return 0;
}
