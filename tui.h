#pragma once

#include "logic.h"

#include <ncurses.h>

/**
 * Initializes the terminal for the game.
 * 
 * Will automatically set its size to the current size of the terminal.
*/
WINDOW *init_game_win();
