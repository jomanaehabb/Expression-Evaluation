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

int checkExp(char* infix) {
    int i = 0, dotCount = 0, flag = 0, flag2 = 0;
    char* token = strtok(infix, " ");

    while (token) {
        //Digit found
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            //Two successive numbers no operator
            if (flag != 0 && flag != -1) {
                printf("\nERROR: Two successive numbers with no operator!\n");
                return 0;
            }

            flag = 1;
            dotCount = 0;
            for (i = 1; token[i] != '\0'; i++) {
                if (token[i] == '.') dotCount++;
                //Number with character no space
                else if (!isdigit(token[i])) {
                    printf("\nERROR: No spaces between operand and operator!\n");
                    return 0;
                }
            }
            //More than one dot
            if (dotCount > 1) {
                printf("\nERROR: More than one dot found in a number!\n");
                return 0;
            }
        }

        else {
            //Operator found
            //two successive operators with not operand
            if (flag != 1 && flag != 0) {
                printf("\nERROR: Two successive operators with no operand!\n");
                return 0;
            }
            if (token[0] == ')' || token[0] == '(') flag = 1;
            else flag = -1;

            //Not defined operator
            if (token[0] != '+' && token[0] != '-' && token[0] != '*' && token[0] != '/' &&
                token[0] != '%' && token[0] != '^' && token[0] != ' ' && token[0] != '\0' &&
                token[0] != '(' && token[0] != ')') {
                printf("\nERROR: Unknown operator entered (ONLY + - * / % ^ are allowed)!\n");
                return 0;
                }

            else if (strlen(token) > 1){ //Each operator should always be of length 1
                //operator with operand no space
                if (isdigit(token[1])) {
                    printf("\nERROR: No spaces between operator and operand!\n");
                    return 0;
                }

                //Two operators with no space
                else {
                    printf("\nERROR: Two successive operators with no space!\n");
                    return 0;
                }
            }
        }
        token = strtok(NULL, " ");
    }

    return 1;
}

int main() {

    /*char infix[] = "2 + ( -2.5 + 3.14 ) * ( -5.4 + 8.1 ) ^ ( -0.5 )";
    printf("Infix expression: %s\n", infix);

    char* postfix = infixToPostfix(infix);
    printf("Postfix expression: %s\n", postfix);

    float result = evaluatePostfix(postfix);
    printf("Result of evaluation: %f\n", result);*/

    char arr[] = "2 - ( 1 ^ 3 ) + 4";
    printf("%d\n", checkExp(arr));

    return 0;
}

/*
else if (token[0] == ')') {
            if (flag2 != 1 || flag2 != 0) {
                printf("\nERROR: ) with no ( found!\n");
                return 0;
            }
            flag = -1;
        }

        else if (token[0] == '(') {
            if (flag2 != -1 || flag2 != 0) {
                printf("\nERROR: ( with no ) found!\n");
                return 0;
            }
            flag = 1;
        }
*/
