//////
#ifndef _STACK_P_H
    #define _STACK_P_H
#endif
//////
#ifndef _STACK_H
    #include "stack.h"
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
//////

//private funcs & consts

static const stack_type STACK_POISON = 0xBADEDA;

static const int DEFAULT_STACK_SIZE_VALUE = 0;

static const int DEFAULT_STACK_CAPACITY_VALUE = 100;

static const int DEFAULT_STACK_CANARY_VALUE = 0xDEDBEDA;

static void Enlarge_Stack(Stack *stack);

static void Reduce_Stack(Stack *stack);

static int Resize_Stack(Stack *stack);

static void Empty_Stack();

static void Insert_Poison(Stack *stack);

static void Copy_Stack(Stack *stack);

static void Recover_Stack(Stack *stack);

static void Dump_Stack(Stack *stack);

//==================================
