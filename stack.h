//////
#ifndef _STACK_H
    #define _STACK_H
#endif
//////
#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _MATH_H
    #include <math.h>
#endif
//////

//public funcs & consts (for user)

typedef int stack_type;

#define print_flag "%d"


typedef struct Stack{

    int left_canary;

    size_t size;

    size_t capacity;

    struct Stack *copy;

    stack_type *data;

    int right_canary;

} Stack;


void Stack_Init(Stack *new_stack);

int Size(Stack *stack);

stack_type Back(Stack *stack);

void Push(Stack *stack, stack_type value);

stack_type Pop(Stack *stack);

void Clear(Stack *stack);

//=====================