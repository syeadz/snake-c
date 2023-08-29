#include "linked_list.h"

#include <stdlib.h>

Node *init_node(int row, int col)
{
    Node *new_node = (Node *)malloc(sizeof(Node));

    new_node->row = row;
    new_node->col = col;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

DLinkedList *init_list(int row, int col)
{
    DLinkedList *new_list = (DLinkedList *)malloc(sizeof(DLinkedList));
    // Going upwards at the beginning, from the middle
    Node *head = init_node(row, col);
    Node *tail = init_node(row + 1, col);

    head->prev = tail;
    tail->next = head;

    new_list->head = head;
    new_list->tail = tail;

    return new_list;
}

void add_node(DLinkedList *list, int row, int col)
{
    Node *new_head = init_node(row, col);

    list->head->next = new_head;
    new_head->prev = list->head;

    list->head = new_head;
}

void rem_last(DLinkedList *list)
{
    Node *cur_tail = list->tail;
    cur_tail->next->prev = NULL;

    list->tail = cur_tail->next;

    free(cur_tail);
}