#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum Dtype {Int, Char, Float};

struct ListNode {
    void *val;
    size_t bytes;
    struct ListNode* next;
};

struct DoubleListNode {
    void *val;
    size_t bytes;
    struct DoubleListNode* next;
    struct DoubleListNode* prev;
};

struct Stack {
    struct ListNode* next;
    size_t len;
    size_t bytes;
};

struct Deque {
    struct DoubleListNode* head;
    struct DoubleListNode* tail;
    size_t len;
    size_t bytes;
};

struct Stack* Stack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack -> next = NULL;
    stack -> len = 0;
    stack -> bytes = 0;
    return stack;
}

struct Deque* Deque() {
    struct Deque* deque = (struct Deque*)malloc(sizeof(struct Deque));
    deque -> head = NULL;
    deque -> tail = NULL;
    deque -> bytes = 0;
    deque -> len = 0;
    return deque;
}

struct DoubleListNode* DoubleListNode() {
    struct DoubleListNode* root = (struct DoubleListNode*)malloc(sizeof(struct DoubleListNode));
    root -> val = NULL;
    root -> next = NULL;
    root -> prev = NULL;
    return root;
}

struct ListNode* ListNode() {
    struct ListNode* root = (struct ListNode*)malloc(sizeof(struct ListNode));
    root -> val = NULL;
    root -> next = NULL;
    return root; 
}

void stack_append(struct Stack* head, void *data, size_t bytes) {
    struct ListNode* root = ListNode();
    root -> val = data;
    root -> bytes = bytes;
    root -> next = head -> next;
    head -> next = root;
    head -> len += 1;
    head -> bytes += bytes;
}

void* stack_pop(struct Stack* head) {
    if (head -> next == NULL) {
        return NULL;
    }
    void* val = head -> next -> val;
    struct ListNode* deleteNode = head -> next;
    head -> next = head -> next -> next;
    head -> len -= 1;
    head -> bytes -= deleteNode -> bytes;
    free(deleteNode);
    return val;
}

void deque_appendleft(struct Deque* queue, void* data, size_t bytes) {
    struct DoubleListNode* root = DoubleListNode();
    root -> val = data;
    root -> bytes = bytes;
    if (queue -> tail == NULL && queue -> head == NULL) {
        queue -> head = root;
        queue -> tail = root;
        queue -> len = 1;
        queue -> bytes = bytes;
        printf("%ld ", queue -> bytes);
        return;
    }
    root -> next = queue -> head;
    queue -> head -> prev = root;
    queue -> head = root;
    queue -> len += 1;
    queue -> bytes += bytes;
    printf("%ld ", queue -> bytes);
    return;
}

void* deque_popleft(struct Deque* queue) {
    if ((queue -> tail == NULL) && (queue -> head == NULL)) {
        return NULL;
    }
    void* val = queue -> head -> val;
    struct DoubleListNode* deleteNode = queue -> head;
    if (queue -> len == 1) {
        queue -> head = NULL;
        queue -> tail = NULL;
    } else {
        queue -> head -> next -> prev = NULL;
        queue -> head = queue -> head -> next;
    }
    queue -> len -= 1;
    queue -> bytes -= deleteNode -> bytes;
    free(deleteNode);
    printf("%ld ", queue -> bytes);
    return val;
}

void deque_append(struct Deque* queue, void *data, size_t bytes) {
    struct DoubleListNode* root = DoubleListNode();
    root -> val = data;
    root -> bytes = bytes;
    if (queue -> tail == NULL && queue -> head == NULL) {
        queue -> tail = root;
        queue -> head = root;
        queue -> len = 1;
        queue -> bytes = bytes;
        printf("%ld ", queue -> bytes);
        return;
    }
    root -> prev = queue -> tail;
    queue -> tail -> next = root;
    queue -> tail = root;
    queue -> bytes += bytes;
    queue -> len += 1;
    printf("%ld ", queue -> bytes);
}

void* deque_pop(struct Deque* queue) {
    if (queue -> tail == NULL && queue -> head == NULL) {
        return NULL;
    }
    void* val = queue -> tail -> val;
    struct DoubleListNode* deleteNode = queue -> tail;
    if (queue -> len == 1) {
        queue -> head = NULL;
        queue -> tail = NULL;
    } else {
        queue -> tail -> prev -> next = NULL;
        queue -> tail = queue -> tail -> prev;
    }
    queue -> len -= 1;
    queue -> bytes -= deleteNode -> bytes;
    free(deleteNode);
    printf("%ld ", queue -> bytes);
    return val;
}

void print_queue(struct Deque* queue) {
    struct DoubleListNode* node = queue -> head;
    printf("\n");
    while (node != NULL) {
        printf("%d ", *(int *)node -> val);
        node = node -> next;
    }
    printf("\n");
    node = queue -> tail;
    while (node != NULL) {
        printf("%d, ", *(int *)node -> val);
        node = node -> prev;
    }
    printf("\n");
}

// int main() {

//     struct Stack* head = Stack();
    
//     int num = 6;
//     stack_append(head, &num, sizeof(int));

//     float flt = .88;
//     stack_append(head, &flt, sizeof(float));
    
//     char chr = 'y';
//     stack_append(head, &chr, sizeof(char));

//     void* data;

//     data = stack_pop(head);

//     printf("%c \n", *(char *)data);
    
//     printf("%f \n", *(float *)stack_pop(head));
//     printf("%d \n", *(int *)stack_pop(head));

//     free(head);
//     // free(data);

//     // data = stack_pop(head);
//     // printf("%f \n", *(float *)data);
//     // free(data);
    
//     // data = stack_pop(head);
//     // printf("%d \n", *(int *)data);
//     // free(data);

//     // data = stack_pop(head);
//     // printf("%p \n", data);

//     // free(head);

//     // struct Deque* queue = Deque();

//     // num = 0;
//     // deque_appendleft(queue, &num, sizeof(int));
//     // num = 1;
//     // deque_appendleft(queue, &num, sizeof(int));
//     // num = -1;
//     // deque_appendleft(queue, &num, sizeof(int));
//     // num = 54;
//     // deque_append(queue, &num, sizeof(int));
//     // num = 34;
//     // deque_append(queue, &num, sizeof(int));
//     // num = 3;
//     // deque_appendleft(queue, &num, sizeof(int));

//     // print_queue(queue);

//     // deque_pop(queue);
//     // print_queue(queue);
//     // deque_popleft(queue);
//     // deque_popleft(queue);
//     // print_queue(queue);
//     // deque_popleft(queue);
//     // deque_popleft(queue);
//     // deque_popleft(queue);
//     // deque_popleft(queue);

//     return 0;
// }