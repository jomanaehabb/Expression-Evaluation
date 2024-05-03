#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

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

// Function to evaluate postfix expression
float evaluatePostfix(char* postfix) {
    Stack *stack = initialize();

    int i = 0;
    float result = 0;
    char ch;

    while ((ch = postfix[i++]) != '\0') {
        if (isdigit(ch) || (ch == '-' && isdigit(postfix[i]))) {
            // Read full number
            float num = 0;
            int sign = 1;
            if (ch == '-') {
                sign = -1;
                ch = postfix[i++];
            }
            while (isdigit(ch) || ch == '.') {
                if (ch != '.') {
                    num = num * 10 + (ch - '0');
                } else {
                    float decimal = 0.1;
                    while (isdigit(postfix[i])) {
                        num += (postfix[i] - '0') * decimal;
                        decimal /= 10.0;
                        i++;
                    }
                }
                ch = postfix[i++];
            }
            push(stack, sign * num);
            i--; // Adjust for the extra increment
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            float operand2 = pop(stack);
            float operand1 = pop(stack);
            switch(ch) {
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '/':
                    push(stack, operand1 / operand2);
                    break;
                case '^':
                    push(stack, pow(operand1, operand2));
                    break;
            }
        }
    }
    result = pop(stack);
    destroyStack(stack);
    return result;
}

int main() {


    return 0;
}
