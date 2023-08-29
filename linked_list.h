#pragma once

/**
 * Struct representing the Node of a Linked List
 *
 * Contains ints row and col as data.
 */
typedef struct Node Node;

struct Node
{
    int row;
    int col;
    Node *next;
    Node *prev;
};

/**
 * Custom Doubly Linked List used soley for the Snake program.
 *
 * Contains head and tail Node pointers.
 */
typedef struct DLinkedList
{
    Node *head;
    Node *tail;
} DLinkedList;

/**
 * Initializes a custom linked list ready for snake and returns its pointer.
 */
DLinkedList *init_list(int row, int col);

/**
 * Adds a new node to the front (head) of the linked list.
 *
 * The new node will have the row and column parameters as data.
 */
void add_node(DLinkedList *list, int row, int col);

/**
 * Removes the last node (tail) of the linked list.
 */
void rem_last(DLinkedList *list);

/**
 * Frees memory from list.
 */
void free_list(DLinkedList *list);
