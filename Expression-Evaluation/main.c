#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

// Function to initialize the stack
Stack* initialize(void) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Fail\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

// Function to push an element onto the stack
void push(Stack* s, float value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Fail\n");
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

//Function displaying all elements of stack
void displaySt(Stack *s) {
    Stack *sCoppy = initialize();

    while (!isEmpty(s)) {
        push(sCoppy, peek(s));
        pop(s);
    }

    while (!isEmpty(sCoppy)) {
        push(s, peek(sCoppy));
        printf("%.0f ", peek(sCoppy));
        pop(sCoppy);
    }
    printf("\n");

    destroyStack(sCoppy);
}

//Filling a stack with an array
void fillStack(Stack *s, float *arr, int size) {
    for (size_t i = 0; i < size; i++){
        push(s, *(arr + i));
    }
}

// Function to pop an item from the stack
float pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    } else {
        return s->items[(s->top)--];
    }
}

// Function to evaluate a postfix expression
float evaluatePostfix(char *postfix) {
    Stack operand_stack;
    initialize(&operand_stack);

    char *ptr = postfix;
    while (*ptr != '\0') {
        if (isdigit(*ptr)) {
            // If the current character is a digit, push it onto the stack
            push(&operand_stack, (float)(*ptr - '0'));
        } else {
            // If the current character is an operator, pop two operands from the stack and perform the operation
            float operand2 = pop(&operand_stack);
            float operand1 = pop(&operand_stack);
            switch (*ptr) {
                case '+':
                    push(&operand_stack, operand1 + operand2);
                    break;
                case '-':
                    push(&operand_stack, operand1 - operand2);
                    break;
                case '*':
                    push(&operand_stack, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Division by zero error\n");
                        exit(EXIT_FAILURE);
                    }
                    push(&operand_stack, operand1 / operand2);
                    break;
                default:
                    printf("Invalid operator\n");
                    exit(EXIT_FAILURE);
            }
        }
        ptr++;
    }

    // The result should be the only item left in the stack
    return pop(&operand_stack);
}

int main() {



    destroyStack(s);
    return 0;
}
