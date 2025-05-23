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

// LINKED LIST FUNCTIONS
// ----------------------------------------

/**
 * Initializes a linked list with a head and tail pointer.
 */
void ll_init();

/**
 * Retrieves the current number of elements in a linked list.
 * 
 * @return An integer representing the size of a linked list.
 */
int ll_size();

/**
 * Inserts a node after a position within a linked list.
 * 
 * @param data a numeric value.
 * @param pos a numeric value denoting a list index where 0 is the starting position.
 */
void ll_ins(const int data, const int pos);

/**
 * Removes a node at a position within a linked list.
 * 
 * @param pos a numeric value denoting a list index where 0 is the starting position.
 */
void ll_rem(const int pos);

/**
 * Appends a node to the beginning of a linked list.
 * 
 * @param data a numeric value.
 */
void ll_push_first(const int data);

/**
 * Appends a node to the end of a linked list.
 * 
 * @param data a numeric value.
 */
void ll_push_last(const int data);

/**
 * Removes the node at the beginning of a linked list.
 *
 * 
 * @return The integer stored from the removed node.
 * exit() is called if linked list is empty or of invalid size.
 */
int ll_pop_first();

/**
 * Removes the node at the end of a linked list.
 * 
 * @return The integer stored from the removed node.
 */
int ll_pop_last();

/**
 * Clears a linked list through deallocation.
 */
void ll_free();

/**
 * Prints each element stored in a linked list.
 */
void ll_print();

/**
 * Locates a Node within a linked list through a specified position and returns it.
 * 
 * @param pos a numeric value denoting a list index where 0 is the starting position.
 * @return The Node at the specified position.
 */
Node* ll_find(const int pos);

// LINKED LIST VARIABLES
// ----------------------------------------

static Node *head, 
            *tail;

// TREE FUNCTIONS
// ----------------------------------------

/**
 * Retrieves the current number of elements in an AVL tree.
 * 
 * @return An integer representing the size of an AVL tree.
 */
int t_size();

/**
 * Balances a tree if uneven.
 */
void t_balance();

/**
 * Inserts a node into an AVL tree.
 * 
 * @param data a numeric value.
 */
void t_ins(const int data);

/**
 * Removes a node from an AVL tree.
 * 
 * @param data a numeric value.
 */
void t_rem(const int data);

/**
 * Clears all elements from an AVL tree through deallocation.
 */
void t_free();

/**
 * Calculates the maximum number of edges from a given TreeNode to a leaf TreeNode.
 * 
 * @param root any given TreeNode
 */
int t_height(const TreeNode *root);

/**
 * Locates a TreeNode within an AVL tree and returns it.
 */
TreeNode* t_find(const int data);

// TREE VARIABLES
// ----------------------------------------

static TreeNode *root = 0;

#endif // _MISC_AVL_H