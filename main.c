#include <time.h>
#include <stdlib.h>

#include "logic.h"
#include "linked_list.h"
#include "tui.h"

// This is basically the game speed
#define TIMEOUTX 50
#define TIMEOUTY 90

void update_points(WINDOW *win, int points);
void handle_gamespeed(WINDOW *win, Snake *snake);
void handle_gamestate(WINDOW *win, GameState *state);

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
    update_points(win, 0);

    // Game loop
    char input;
    while (input != 'q')
    {
        // Timeout will depend on direction moving, X is set faster because Y is
        // naturally faster
        handle_gamespeed(win, &snake);
        handle_gamestate(win, &state);

        // wgetch will timeout if nothing is pressed, returning an ERR
        input = wgetch(win);
        if (input == ERR)
        {
            move_snake(win, &state, &snake);
            wrefresh(win);
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

void update_points(WINDOW *win, int points)
{
    char str[10];
    sprintf(str, "Score: %d", points);

    // mvwprintw(win, 1, 2, str);
    mvwprintw(win, 0, COLS / 2 - 9, str);
}

void handle_gamespeed(WINDOW *win, Snake *snake) {
        Dir cur_dir = snake->dir;
        if (cur_dir == Up || cur_dir == Down)
        {
            wtimeout(win, TIMEOUTY);
        }
        else
        {
            wtimeout(win, TIMEOUTX);
        }
}


void handle_gamestate(WINDOW *win, GameState *state)
{
    if (state->died)
    {
        mvwaddstr(win, LINES / 2, COLS / 2 - 13, "YOU HAVE DIED"); // TODO: add restart option
    }
    else if (state->ate)
    {
        state->ate = false;
        state->points++;
        update_points(win, state->points);
        spawn_food(win);
        wrefresh(win);
    }
}
