#include "logic.h"

#include <stdlib.h>

int move_snake(WINDOW *win, State *state, Snake *snake)
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

        // TODO: check window bounds
        // Check what the head is moving to
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
        int lower = 0;
        int num = (rand() % (upper - lower + 1)) + lower;
        return num;
}

void spawn_food(WINDOW *win)
{
        int max_x = getmaxx(win);
        int max_y = getmaxy(win);

        mvwaddch(win, ran_num(max_y), ran_num(max_x), FOOD_CHAR);
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