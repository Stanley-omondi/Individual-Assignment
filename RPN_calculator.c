#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *stack) {
    stack->top = -1;
}

bool is_empty(Stack *stack) {
    return stack->top == -1;
}

bool is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
}

bool is_operand(char ch) {
    return isdigit(ch);
}

void push(Stack *stack, int value) {
    stack->top++;
    stack->data[stack->top] = value;
}

int pop(Stack *stack) {
    int value = stack->data[stack->top];
    stack->top--;
    return value;
}

int precedence(char operator) {
    switch (operator) {
        case '*':
        case '/':
        case '%':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

void infix_to_postfix(char *expression, char *postfix) {
    Stack stack;
    initialize(&stack);
    int i = 0, j = 0;
    
    while (expression[i] != '\0') {
        char ch = expression[i];
        
        if (is_operand(ch)) {
            postfix[j] = ch;
            j++;
        } else if (is_operator(ch)) {
            while (!is_empty(&stack) && is_operator(stack.data[stack.top]) && precedence(stack.data[stack.top]) >= precedence(ch)) {
                postfix[j] = pop(&stack);
                j++;
            }
            push(&stack, ch);
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (!is_empty(&stack) && stack.data[stack.top] != '(') {
                postfix[j] = pop(&stack);
                j++;
            }
            pop(&stack); // Pop the '(' from the stack
        }
        
        i++;
    }
    
    while (!is_empty(&stack)) {
        postfix[j] = pop(&stack);
        j++;
    }
    
    postfix[j] = '\0';
}

int evaluate_postfix(char *postfix) {
    Stack stack;
    initialize(&stack);
    int i = 0;
    
    while (postfix[i] != '\0') {
        char ch = postfix[i];
        
        if (isdigit(ch)) {
            push(&stack, ch - '0');
        } else if (is_operator(ch)) {
            int b = pop(&stack);
            int a = pop(&stack);
            
            switch (ch) {
                case '+':
                    push(&stack, a + b);
                    break;
                case '-':
                    push(&stack, a - b);
                    break;
                case '*':
                    push(&stack, a * b);
                    break;
                case '/':
                    push(&stack, a / b);
                    break;
                case '%':
                    push(&stack, a % b);
                    break;
            }
        }
        
        i++;
    }
    
    return pop(&stack);
}

int main() {
    char expression[MAX_SIZE];
    printf("Enter an infix expression: ");
    fgets(expression, sizeof(expression), stdin);
    
    // Remove the trailing newline character
    if (expression[strlen(expression) - 1] == '\n') {
        expression[strlen(expression) - 1] = '\0';
    }
    
    char postfix[MAX_SIZE];
    infix_to_postfix(expression, postfix);
    
    printf("Postfix expression: %s\n", postfix);
    
    int result = evaluate_postfix(postfix);
    printf("Result: %d\n", result);
    
    return 0;
}