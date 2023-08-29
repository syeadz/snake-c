#pragma once

#define BODY_CHAR 'X'
#define BODY_COL COLOR_GREEN

#define HEAD_CHAR '@'
#define HEAD_COL COLOR_MAGENTA

#define FOOD_CHAR 'O'
#define FOOD_COL COLOR_YELLOW

#include <ncurses.h>

#include "linked_list.h"

/**
 * Enum representing the 4 different directions the Snake can move.
*/
typedef enum
{
    Up,
    Down,
    Left,
    Right,
} Dir;

/**
 * Struct representing the snake, indicating its direction and its body.
 * 
 * The body is represented as a linked list, with each Node being a position.
*/
typedef struct Snake
{
    Dir dir;
    DLinkedList *body;
} Snake;

/**
 * Struct representing the state of the game.
 * 
 * Keeps track of whether the snake ate, died, as well as the points received so far.
*/
typedef struct GameState
{
    bool ate;
    bool died;
    int points;
} GameState;

/**
 * Handles the movement and display of the snake on the screen.
 * 
 * Will move the snake by one each time it is called. It will not remove the tail if the snake 
 * has eaten.
*/
int move_snake(WINDOW *win, GameState *state, Snake *snake);

/**
 * Spawns food somewhere random on the screen.
*/
void spawn_food(WINDOW *win);

/**
 * Converts user input into a direction which is then set for the snake.
*/
int set_dir(Snake *snake, char input);