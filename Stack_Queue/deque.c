#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


struct dequeNode {
    int val;
    struct dequeNode* next;
    struct dequeNode* prev;
};

struct deque {
    struct dequeNode* head;
    struct dequeNode* tail;
    int len;
};


struct deque* deque() {
    struct deque* queue = (struct deque*)malloc(sizeof(struct deque));
    queue -> head = NULL;
    queue -> tail = NULL;
    queue -> len = 0;
    return queue;
}

struct dequeNode* new_deque_node(int val) {
    struct dequeNode* node = (struct dequeNode*)malloc(sizeof(struct dequeNode));
    node -> next = NULL;
    node -> prev = NULL;
    node -> val = val;
    return node;
}

void append(struct deque* queue, int value) {
    struct dequeNode* node = new_deque_node(value);
    if (queue -> len == 0) {
        queue -> tail = node;
        queue -> head = node;
        queue -> len = 1;
        return;
    }
    node -> prev = queue -> tail;
    queue -> tail -> next = node;
    queue -> tail = node;
    queue -> len = (queue -> len) + 1;
    return;
}

int pop(struct deque* queue) {
    if (queue -> len == 0) {
        return NULL;
    }
    int value = queue -> tail -> val;
    struct dequeNode* lastNode = queue -> tail;
    if (queue -> len == 1) {
        queue -> head = NULL;
        queue -> tail = NULL;
    } else {
        queue -> tail -> prev -> next = NULL;
        queue -> tail = queue -> tail -> prev;
    }
    free(lastNode);
    queue -> len = (queue -> len) - 1;
    return value;
}

void appendleft(struct deque* queue, int value) {
    struct dequeNode* node = new_deque_node(value);
    if (queue -> len == 0) {
        queue -> head = node;
        queue -> tail = node;
        queue -> len = 1;
        return;
    }
    node -> next = queue -> head;
    queue -> head -> prev = node;
    queue -> head = node;
    queue -> len = (queue -> len) + 1;
    return;
}

int popleft(struct deque* queue) {
    if (queue -> len == 0) {
        return NULL;
    }
    int value = queue -> head -> val;
    struct dequeNode* firstNode = queue -> head;
    if (queue -> len == 1) {
        queue -> head = NULL;
        queue -> tail = NULL;
    } else {
        queue -> head = queue -> head -> next;
        queue -> head -> prev = NULL;
    }
    free(firstNode);
    queue -> len = (queue -> len) - 1;
    return value;
}

int peek(struct deque* queue) {
    int value = queue -> tail -> val;
    return value;
}

int peekleft(struct deque* queue) {
    int value = queue -> head -> val;
    return value;
}

int len(struct deque* queue) {
    return queue -> len;
}

bool is_empty(struct deque* queue) {
    if (queue -> len == 0) {
        return true;
    }
    return false;
}

void clear_deque(struct deque* queue) {
    while (queue -> len != 0) {
        pop(queue);
    }
    return;
}

void print_deque(struct deque* queue) {
    struct dequeNode* node = queue -> head;
    while (node != NULL) {
        printf("%d", node -> val);
        node = node -> next;
        if (node != NULL) {
            printf(", ");
        }
    }
    printf("\n");
    return;
}

int main() {

    struct deque* stack = deque();

    append(stack, 1);
    append(stack, 2);
    append(stack, 3);
    appendleft(stack, 4);
    appendleft(stack, 5);
    appendleft(stack, 6);

    print_deque(stack);

    printf("%d \n", is_empty(stack));

    clear_deque(stack);

    popleft(stack);
    pop(stack);

    free(stack);

    return 0;
}