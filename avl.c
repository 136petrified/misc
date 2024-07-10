#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

int size() {
    int count = 0;
    for (Node *temp = head; temp; temp = temp->next)
        count++;

    return count;
}

void insert(const int *data, const int *pos) {
    // Create new node and attach it at position
    int s = size();

    if (pos == 0) {
        push_front(data);
    } else if (pos == s - 1) {
        push_back(data);
    } else {
        Node *temp = (Node *) malloc(sizeof(Node)),
             *dest = find(pos); // dest->next = temp

        temp->data = data;
        temp->next = dest->next;
        dest->next = temp;  // dest->next can now be safely overwritten
    }
}

Node* find(const int *pos) {
    // Check for valid position
    if (pos < 0 || pos >= size()) {
        fprintf(stderr, "ERROR: Invalid size.");
        exit(EXIT_FAILURE); // Exit out from error
    }

    Node *temp = head;
    for (int i = 0; i < pos; ++i)
        temp = temp->next;

    return temp;
}