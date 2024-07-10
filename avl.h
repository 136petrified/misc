#ifndef _MISC_AVL_H
#define _MISC_AVL_H

typedef struct Node {
    int data;
    struct Node *next; // default: NULL
} Node;

typedef struct TreeNode {
    int data;
    struct TreeNode *left; // default: NULL
    struct TreeNode *right; // default: NULL
} TreeNode;

// NODE FUNCTIONS
// ----------------------------------------

/**
 * Initializes a linked list with a head and tail pointer.
 */
void node_init();

/**
 * Retrieves the current number of elements in a linked list.
 * 
 * @return An integer representing the size of a linked list.
 */
int size();

/**
 * Inserts a node after a position within a linked list.
 * 
 * @param data a numeric value.
 * @param pos a numeric value denoting a list index where 0 is the starting position.
 */
void ins(const int data, const int pos);

/**
 * Removes a node at a position within a linked list.
 * 
 * @param pos a numeric value denoting a list index where 0 is the starting position.
 */
void rem(const int pos);

/**
 * Appends a node to the beginning of a linked list.
 * 
 * @param data a numeric value.
 */
void push_first(const int data);

/**
 * Appends a node to the end of a linked list.
 * 
 * @param data a numeric value.
 */
void push_last(const int data);
int pop_first();
int pop_last();
void _free();
void print();

Node* find(const int pos);

// NODE VARIABLES
// ----------------------------------------

static Node *head = 0, 
            *tail = 0;

// TREE FUNCTIONS
// ----------------------------------------

void t_size();
void t_balance();
void t_insert(const int data, const int pos);
void t_remove(const int pos);
void t_free();
void height();

// TREE VARIABLES
// ----------------------------------------

static TreeNode *root = 0;

#endif // _MISC_AVL_H