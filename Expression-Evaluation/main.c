#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    float data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

// Function to initialize the stack
Stack* initialize() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("fail\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

// Function to push an element onto the stack
void push(Stack* s, float value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("fail\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

// Function to pop an element from the stack
float pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = s->top;
    float poppedValue = temp->data;
    s->top = temp->next;
    free(temp);
    return poppedValue;
}

// Function to return the top element of the stack without removing it
float peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return s->top->data;
}

// Function to check if the stack is empty
int isEmpty(Stack* s) {
    return (s->top == NULL);
}

// Function to free the memory allocated for the stack
void destroyStack(Stack* s) {
    while (!isEmpty(s)) {
        pop(s);
    }
    free(s);
}

int main() {


    return 0;
}
