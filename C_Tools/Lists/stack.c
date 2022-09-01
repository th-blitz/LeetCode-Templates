#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* Node() {
    struct ListNode* root = (struct ListNode*)malloc(sizeof(struct ListNode));
    root -> next = NULL;
    root -> val = NULL; 
    return root; 
}

void append(struct ListNode* root, int val) {
    struct ListNode* node = Node(); 
    node -> val = val;
    node -> next = root -> next;
    root -> next = node;
}

int pop(struct ListNode* root) {
    if (root -> next == NULL) {
        return NULL;
    }
    int val = root -> next -> val;
    struct ListNode* deleteNode = root -> next;
    root -> next = root -> next -> next;
    free(deleteNode);
    return val;
}

int peek(struct ListNode* root) {
    if (root -> next == NULL) {
        return NULL;
    }
    int val = root -> next -> val;
    return val;
}

void freeStack(struct ListNode* stack) {
    while (peek(stack) != NULL) {
        pop(stack);
    }
    free(stack);
}

int main() {
    struct ListNode* stack = Node();
    append(stack, 2);
    append(stack, 3);
    append(stack, 4);

    printf("%d ", pop(stack));
    
    freeStack(stack);

    
    return 0;
}

                 