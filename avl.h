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

/**
 * Removes the node at the beginning of a linked list.
 *
 * 
 * @return The integer stored from the removed node.
 * exit() is called if linked list is empty or of invalid size.
 */
int pop_first();

/**
 * Removes the node at the end of a linked list.
 * 
 * @return The integer stored from the removed node.
 */
int pop_last();

/**
 * Clears a linked list through deallocation.
 */
void _free();

/**
 * Prints each element stored in a linked list.
 */
void print();

/**
 * Locates a Node within a linked list through a specified position.
 * 
 * @param pos a numeric value denoting a list index where 0 is the starting position.
 * @return The Node at the specified position.
 */
Node* find(const int pos);

// NODE VARIABLES
// ----------------------------------------

static Node *head = 0, 
            *tail = 0;

// TREE FUNCTIONS
// ----------------------------------------

/**
 * Locates a Node within a linked list through a specified position.
 * 
 * @param pos a numeric value denoting a list index where 0 is the starting position.
 * @return The Node at the specified position.
 */
int t_size();
void t_balance();
void t_ins(const int data, const int pos);
void t_rem(const int pos);
void t_free();
void height();
void t_find();

// TREE VARIABLES
// ----------------------------------------

static TreeNode *root = 0;

#endif // _MISC_AVL_H