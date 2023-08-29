#pragma once

#define BODY_CHAR 'X'
#define BODY_COL COLOR_GREEN

#define HEAD_CHAR '@'
#define HEAD_COL COLOR_MAGENTA

#define FOOD_CHAR 'O'
#define FOOD_COL COLOR_YELLOW

#define TIMEOUTX 50
#define TIMEOUTY 90

#include <ncurses.h>

#include "linked_list.h"

typedef enum
{
    Up,
    Down,
    Left,
    Right,
} Dir;

typedef struct Snake
{
    Dir dir;
    DLinkedList *body;
} Snake;

typedef struct State
{
    bool ate;
    bool died;
    int points;
} State;

int move_snake(WINDOW *win, State *state, Snake *snake);
void spawn_food(WINDOW *win);
int set_dir(Snake *snake, char input);