#pragma once

typedef struct Node Node;  // Forward declaration

struct Node
{
    int row;
    int col;
    Node *next;
    Node *prev;
};

typedef struct DLinkedList
{
    Node *head;
    Node *tail;
} DLinkedList;

DLinkedList *init_list(int row, int col);
void add_node(DLinkedList* list, int row, int col);
void rem_last(DLinkedList* list);