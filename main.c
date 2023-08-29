#include <time.h>
#include <stdlib.h>

#include "logic.h"
#include "linked_list.h"
#include "tui.h"

// This is basically the game speed
#define TIMEOUTX 50
#define TIMEOUTY 90

void update_points(WINDOW *win, int points);
void handle_gamespeed(WINDOW *g_win, Snake *snake);
void handle_gamestate(WINDOW *g_win, WINDOW *i_win, GameState *state);

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
    WINDOW *g_win = init_game_win();
    WINDOW *i_win = init_info_win();
    GameState state = {.ate = false, .died = false, .points = 0};
    Snake snake = {.body = init_list(LINES / 2, COLS / 2), .dir = Up};
    move_snake(g_win, &state, &snake);
    spawn_food(g_win);
    wrefresh(g_win);
    update_points(i_win, 0);
    wrefresh(i_win);

    // Game loop
    char input;
    while (input != 'q')
    {
        // Timeout will depend on direction moving, X is set faster because Y is
        // naturally faster
        handle_gamespeed(g_win, &snake);
        handle_gamestate(g_win, i_win, &state);

        // wgetch will timeout if nothing is pressed, returning an ERR
        input = wgetch(g_win);
        if (input == ERR)
        {
            move_snake(g_win, &state, &snake);
            wrefresh(g_win);
            continue;
        }

        set_dir(&snake, input);
        move_snake(g_win, &state, &snake);

        wrefresh(g_win);
    }

    // End
    endwin();
    return 0;
}

void update_points(WINDOW *win, int points)
{
    char str[10];
    sprintf(str, "Score: %d", points);

    mvwprintw(win, 1, 2, str);
}

void handle_gamespeed(WINDOW *g_win, Snake *snake) {
        Dir cur_dir = snake->dir;
        if (cur_dir == Up || cur_dir == Down)
        {
            wtimeout(g_win, TIMEOUTY);
        }
        else
        {
            wtimeout(g_win, TIMEOUTX);
        }
}


void handle_gamestate(WINDOW *g_win, WINDOW *i_win, GameState *state)
{
    if (state->died)
    {
        mvwaddstr(g_win, LINES / 2, COLS / 2, "YOU HAVE DIED"); // TODO: center and add restart option
    }
    else if (state->ate)
    {
        state->ate = false;
        state->points++;
        update_points(i_win, state->points);
        spawn_food(g_win);
        wrefresh(g_win);
        wrefresh(i_win);
    }
}
