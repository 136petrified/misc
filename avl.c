#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

void node_init() {
    if (size() == 0) {
        assert(head == NULL);
        assert(tail == NULL);
        assert(head == tail);
    }
}

int size() {
    int count = 0;
    for (Node *temp = head; temp != NULL; temp = temp->next)
        count++;

    return count;
}

void insert(const int *data, const int *pos) {
    // Create new node and attach it at position
    int s = size();

    if (pos == 0) {
        push_first(data);
    } else if (*pos == s - 1) {
        push_last(data);
    } else {
        Node *temp = (Node *) malloc(sizeof(Node)),
             *dest = find(*pos); // dest->next = temp

        temp->data = *data;
        temp->next = dest->next;
        dest->next = temp;  // dest->next can now be safely overwritten
    }
}

void remove(const int *pos) {
    // Remove node at position
    int s = size();

    if (pos == 0) {
        pop_first();
    } else if (*pos == s - 1) {
        pop_last();
    } else {
        Node *temp = find(*pos),
             *prev = find(*pos - 1);

        prev->next = temp->next;
        free(temp); // Free this node
    }
}

void push_first(const int *data) {
    Node *temp = (Node *) malloc(sizeof(Node));
    
    temp->data = *data;
    temp->next = head;
    head = temp;
}

void push_last(const int *data) {
    Node *temp = (Node *) malloc(sizeof(Node));
    
    temp->data = *data;
    temp->next = 0;

    if (tail != NULL) {
        tail->next = temp;
        tail = temp;
    } else {
        tail = temp;
        head = tail;
    }
}

int pop_first() {
    int s = size(),
        v;  // Value to return

    if (s == 1) {
        v = head->data;
        free(head);
    } else if (s > 1) {
        v = head->data;
        Node *temp = head;
        head = temp->next;
        free(temp);
    } else {
        fprintf(stderr, "ERROR: Cannot pop from empty or invalid list");
        exit(EXIT_FAILURE); // Exit out from error
    }

    return v;
}

int pop_last() {
    int s = size(),
        v;  // Value to return

    if (s == 1) {
        v = tail->data;
        free(tail);
    } else if (s > 1) {
        Node *dest = find(s - 2);

        v = tail->data;
        dest->next = 0;
        free(tail);
        tail = dest;
    } else {
        fprintf(stderr, "ERROR: Cannot pop from empty or invalid list");
        exit(EXIT_FAILURE); // Exit out from error
    }

    return v;
}

Node* find(const int *pos) {
    // Check for valid position
    if (*pos < 0 || *pos >= size()) {
        fprintf(stderr, "ERROR: Invalid size.");
        exit(EXIT_FAILURE); // Exit out from error
    }

    Node *temp = head;
    for (int i = 0; i < *pos - 1; ++i)
        temp = temp->next;

    return temp;
}