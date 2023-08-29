#include <time.h>
#include <stdlib.h>

#include "logic.h"
#include "linked_list.h"
#include "tui.h"

// This is basically the game speed
#define TIMEOUTX 50
#define TIMEOUTY 90

// Function prototypes
/**
 * Updates the points shown on screen.
*/
void update_points(WINDOW *win, int points);

/**
 * Handles timeout for character input.
*/
void handle_gamespeed(WINDOW *win, Snake *snake);

/**
 * Handles the state flags.
*/
void handle_gamestate(WINDOW *win, GameState *state);

/**
 * Resets gamestate for a new game.
*/
void reset_gamestate(GameState *state, Snake *snake);


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
    int high_score = 0;
    char input;
    char str[15];

loop:
    // Game loop
    move_snake(win, &state, &snake);
    spawn_food(win);
    update_points(win, state.points);
    sprintf(str, "High Score: %d", high_score);
    mvwprintw(win, 0, COLS / 2 - 4, str);
    wrefresh(win);

    while (input != 'q' && !state.died)
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

    if (1) // End game screen
    {
        wtimeout(win, 10000);
        wclear(win);
        box(win, 0, 0);

        char str[15];
        sprintf(str, "Score: %d", state.points);
        mvwaddstr(win, LINES / 2 - 4, COLS / 2 - 9 / 2, str);

        if (state.points > high_score)
        {
            high_score = state.points;
            mvwaddstr(win, LINES / 2 - 2, COLS / 2 - 14 / 2, "New High Score!");
        }

        sprintf(str, "High Score: %d", high_score);
        mvwaddstr(win, LINES / 2 - 3, COLS / 2 - 14 / 2, str);

        mvwaddstr(win, LINES / 2, COLS / 2 - 8 / 2, "YOU LOSE");
        mvwaddstr(win, LINES / 2 + 2, COLS / 2 - 17 / 2, "Press r to retry");
        mvwaddstr(win, LINES / 2 + 3, COLS / 2 - 16 / 2, "Press q to quit");

        wrefresh(win);
        while (input != ERR)
        {
            input = wgetch(win);
            if (input == 'r')
            {
                input = '@';
                reset_gamestate(&state, &snake);
                wclear(win);
                box(win, 0, 0);
                goto loop;
            }
            else if (input == 'q')
            {
                break;
            }
        }
    }

    // End
    endwin();
    return 0;
}

void update_points(WINDOW *win, int points)
{
    char str[15];
    sprintf(str, "Score: %d", points);
    mvwprintw(win, 0, COLS / 2 - 19, str);
}

void handle_gamespeed(WINDOW *win, Snake *snake)
{
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
    }
    if (state->ate)
    {
        state->ate = false;
        state->points++;

        update_points(win, state->points);
        spawn_food(win);
        wrefresh(win);
    }
}

void reset_gamestate(GameState *state, Snake *snake)
{
    state->ate = false;
    state->died = false;
    state->points = 0;

    snake->dir = Up;
    free_list(snake->body);
    snake->body = init_list(LINES / 2, COLS / 2);
}