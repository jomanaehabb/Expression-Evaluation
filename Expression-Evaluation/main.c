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
        printf("%c ", (char)peek(sCoppy));
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

int precedence(char oper) {
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

char* infixToPostfix(char *infix) {
    char* postfix = malloc(strlen(infix) + 1);
    postfix[0] = 0; //Cleaning garbage values
    char* temp[2] = {'0', '\0'}; //Used to append the operator as string to the postfix string
    Stack *s = initialize();
    char* token = strtok(infix, " ");
    while (token) {
        //If the token is a number insert it in the output
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                strcat(postfix, token);
                strcat(postfix, " ");
        }

        //If the token is ) pop all elements in stack until ( is found
        else if (token[0] == ')') {
            while ((char)peek(s) != '(' && !isEmpty(s)) {
                temp[0] = (char)pop(s);
                strcat(postfix, temp);
                strcat(postfix, " ");
            }
            pop(s); //Removing the (
        }

        //If the stack is empty just push the token
        else if (isEmpty(s)) {
                push(s, token[0]);
        }

        //If the token is an operator
        else {
            //Check the priority of the operator if higher than the top of stack
            //push to stack
            while (!isEmpty(s) && precedence(token[0]) <= precedence((char)peek(s)) && (char)peek(s) != '(') {
                temp[0] = (char)pop(s);
                strcat(postfix, temp);
                strcat(postfix, " ");
               }
            push(s, token[0]);
            }
        token = strtok(NULL, " ");
    }

    while (!isEmpty(s)) {
        temp[0] = (char)pop(s);
        strcat(postfix, temp);
        strcat(postfix, " ");
    }

    destroyStack(s);
    return postfix;
}


int main() {

    char infixx[] = "2 + ( -2.5 + 3.14 ) * ( -5.4 + 8.1 ) ^ ( -0.5 )";
    printf("%s\n", infixToPostfix(infixx));

    return 0;
}

