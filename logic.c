#include "logic.h"

#include <stdlib.h>

int move_snake(WINDOW *win, GameState *state, Snake *snake)
{
        // head
        int row = snake->body->head->row;
        int col = snake->body->head->col;

        // TODO: add color
        mvwaddch(win, row, col, BODY_CHAR);

        switch (snake->dir)
        {
        case Up:
                row--;
                break;
        case Down:
                row++;
                break;
        case Left:
                col--;
                break;
        case Right:
                col++;
                break;
        default:
                break;
        }

        int max_x = getmaxx(win);
        int max_y = getmaxy(win);

        if (row == 0)
                row = max_y - 2;
        if (row == max_y - 1)
                row = 1;
        if (col == 0)
                col = max_x - 2;
        if (col == max_x - 1)
        {
                col = 1;
        }

        char moving_to = mvwinch(win, row, col);
        if (moving_to == BODY_CHAR)
        {
                state->died = true;
                return 1;
        }

        mvwaddch(win, row, col, HEAD_CHAR);
        add_node(snake->body, row, col);

        if (moving_to == FOOD_CHAR)
        {
                state->ate = true;
        }
        else
        {
                // update tail (no food)
                row = snake->body->tail->row;
                col = snake->body->tail->col;

                mvwaddch(win, row, col, ' ');
                rem_last(snake->body);
        }

        return 0;
}

int ran_num(int upper)
{
        int lower = 1; // Don't spawn on border
        int num = (rand() % (upper - lower + 1)) + lower;
        return num;
}

void spawn_food(WINDOW *win)
{
        int max_x = getmaxx(win);
        int max_y = getmaxy(win);

        int ran_x, ran_y;

        // Make sure it doesn't spawn on the snake
        bool valid = false;
        while (!valid)
        {
                // -2 to avoid spawning on border
                ran_y = ran_num(max_y - 2);
                ran_x = ran_num(max_x - 2);

                char spot = mvwinch(win, ran_y, ran_x);
                if (spot != BODY_CHAR)
                        valid = true;
        }
        mvwaddch(win, ran_num(max_y - 2), ran_num(max_x - 2), FOOD_CHAR);
}

int set_dir(Snake *snake, char input)
{
        Dir cur_dir = snake->dir;
        switch (input)
        {
        case 'w':
                if (cur_dir != Down)
                        snake->dir = Up;
                break;
        case 's':
                if (cur_dir != Up)
                        snake->dir = Down;
                break;
        case 'a':
                if (cur_dir != Right)
                        snake->dir = Left;
                break;
        case 'd':
                if (cur_dir != Left)
                        snake->dir = Right;
                break;
        default:
                return 1;
        }
        return 0;
}