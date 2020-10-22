//////
#ifndef FUNCS_PUB_H
    #define FUNCS_PUB_H
#endif
//////
#ifndef STACK_DECL_H
    #include "stack_decl.h"
#endif

#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _MATH_H
    #include <math.h>
#endif

#ifndef _ASSERT_H
    #include <assert.h>
#endif
//////


//public funcs

Stack *Init_Stack();

size_t Size(Stack *stack);

stack_type Back(Stack *stack);

void Push(Stack *stack, stack_type value);

stack_type Pop(Stack *stack);

void Clear(Stack *stack);

void Destruct_Stack(Stack *stack);

//==================