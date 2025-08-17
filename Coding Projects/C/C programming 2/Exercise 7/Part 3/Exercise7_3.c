#include <stdio.h>

#define MAX_STACK_SIZE 100

typedef struct{

    char data[MAX_STACK_SIZE];              // store characters
    int top;                                // index of top element in data array
} Stack;

int Push(Stack *stack, char item){

    if (stack->top == MAX_STACK_SIZE){      // check if stack is full

        return -1;            //print error if full
    } 

    else{

        stack->data[stack->top] = item;
        stack->top++;
        return 0;
    }
}

char Pop(Stack *stack){

    if (stack->top == -1){                  // check if stack is empty              //dont pop
        return 0;
    }
    else{                                   // if not empty 
        stack->top--;                       // decrement top
        return stack->data[stack->top];     // return char that is popped off stack
    }
}

int main(int argc, char *argv[]){

    FILE *file;
    Stack stack;
    stack.top = 0;
    char c;
    int ret = 0;

    if (argc != 2){                     // error check command line args
        puts("Wrong number of command-line arguments!\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    
    if (file == NULL){                  // open file with error checking
        puts("Error opening file");
        return 1;
    }

    c = fgetc(file);
    while ((c != EOF) && (ret != -1)){

        ret = Push(&stack, c);                 // Push() characters from the file onto our stack
        c = fgetc(file);
    }
    if (ret == -1){
        puts("Stack full");
    }
 
    fclose(file);

    while ((c = Pop(&stack)) != 0) {
        putchar(c); // Print the character
    }

    return 0;
}