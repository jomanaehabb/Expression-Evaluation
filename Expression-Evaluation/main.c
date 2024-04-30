#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

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


char* infixToPostfix(char *infix) {
    char postfix[SIZE];
    int i = 0;
    Stack *s = initialize();
    char* token = strtok(infix, " ");
    while (token) {
        //If the token is a number insert it in the output
        if (isnum(token)) {
            if (i <= SIZE - 1) {
                *(postfix + i) = atoi(token);
                i++;
            }
            else
                printf("ERROR: Max size for expression reached!\n");
        }
        //If the token is ) pop all elements in stack until ( is found
        else if (token == ')') {
            while ((char)peek(s) != '(') {
                *(postfix + i) = pop(s);
                i++;
            }
            pop(s); //Removing the (
        }
        //If the token is an operator
        else {
            //If the stack is empty just push the token
            if (isEmpty(s)) push(s, (char)*token);
            else {
                //Check the priority of the operator if higher than the top of stack
                //push to stack
               if (percedence((char)*token) > percedence((char)peek(s))) {
                    push(s, (char)*token);
               }
               else{
                    *(postfix + i) = pop(s);
                    i++;
                }
            }
        }
        token = strtok(NULL, " ");
    }

    destroyStack(s);
    return postfix;
}

int percedence(char oper) {
    switch (oper) {
    case '+':
    case '-':
        return 0;

    case '*':
    case '/':
    case '%':
        return 1;

    case '^':
        return 2;

    case '(':
        return 3;

    default:
        printf("ERROR: Operation not declared!\n");
        exit(-1);
    }
}

int main() {

    char infixx[] = "1 + 2 * 4 + 3";
    printf("%s\n", infixToPostfix(infixx));

    return 0;
}
