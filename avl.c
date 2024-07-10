#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

void ll_init() {
    Node *head = 0,
         *tail = 0;
}

int ll_size() {
    int count = 0;
    for (Node *temp = head; temp != NULL; temp = temp->next)
        count++;

    return count;
}

void ll_ins(const int data, const int pos) {
    // Create new node and attach it at position
    int s = ll_size();

    if (pos == 0) {
        ll_push_first(data);
    } else if (pos == s - 1) {
        ll_push_last(data);
    } else {
        Node *temp = (Node *) malloc(sizeof(Node)),
             *dest = ll_find(pos); // dest->next = temp

        temp->data = data;
        temp->next = dest->next;
        dest->next = temp;  // dest->next can now be safely overwritten
    }
}

void ll_rem(const int pos) {
    // Remove node at position
    int s = ll_size();

    if (pos == 0) {
        ll_pop_first();
    } else if (pos == s - 1) {
        ll_pop_last();
    } else {
        Node *temp = ll_find(pos),
             *prev = ll_find(pos - 1);

        prev->next = temp->next;
        free(temp); // Free this node
    }
}

void ll_push_first(const int data) {
    Node *temp = (Node *) malloc(sizeof(Node));
    
    temp->data = data;
    temp->next = head;
    head = temp;
}

void ll_push_last(const int data) {
    Node *temp = (Node *) malloc(sizeof(Node));
    
    temp->data = data;
    temp->next = 0;

    if (tail != NULL) {
        tail->next = temp;
        tail = temp;
    } else {
        tail = temp;
        head = tail;
    }
}

int ll_pop_first() {
    int s = ll_size(),
        v;  // Value to return

    if (s == 1) {
        v = head->data;
        free(head);
        head = 0;
        tail = 0;
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

int ll_pop_last() {
    int s = ll_size(),
        v;  // Value to return

    if (s == 1) {
        v = tail->data;
        free(tail);
        tail = 0;
        head = tail;
    } else if (s > 1) {
        Node *dest = ll_find(s - 2);

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

void ll_free() {
    while (ll_size())
        ll_pop_last();
}

void ll_print() {
    for (Node *temp = head; temp != NULL; temp = temp->next)
        printf("%d\n", temp->data);
}

Node* ll_find(const int pos) {
    // Check for valid position
    if (pos < 0 || pos >= ll_size()) {
        fprintf(stderr, "ERROR: Invalid size.");
        exit(EXIT_FAILURE); // Exit out from error
    }

    Node *temp = head;
    for (int i = 0; i < pos - 1; ++i)
        temp = temp->next;

    return temp;
}