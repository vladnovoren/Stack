//////
#ifndef FUNCS_PRV_H
    #define FUNCS_PRV_H
#endif
//////
#ifndef FUNCS_PUB_H
    #include "funcs_pub.h"
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


//private funcs & consts

struct Stack{

    int left_cnry;

    size_t size;

    size_t cpcty;

    struct Stack *copy;

    stack_type *data;

    int right_cnry;

};

static const stack_type STACK_POISON  = 0xBADEDA;

static const int DFLT_STACK_SIZE_VAL  = 0;

static const int DFLT_STACK_CPCTY_VAL = 100;

static const unsigned long long DFLT_STACK_CNRY_VAL = 0xBEDADEA;

//==========
void Set_Defaults(Stack *stack);

void Set_Defaults_Local(Stack *stack);
//==========

//==========
void Enlarge_Stack(Stack *stack);

void Enlarge_Stack_Local(Stack *stack);
//==========

//==========
void Reduce_Stack(Stack *stack);

void Reduce_Stack_Local(Stack *stack);
//==========

//==========
int Resize_Stack(Stack *stack);

int Resize_Stack_Local(Stack *stack);
//==========

//==========
void Insert_Poison(Stack *stack);

void Insert_Poison_Local(Stack *stack);
//==========

//==========
void Copy_Stack(Stack *stack); 
//==========

//==========
void Clear_Stack_Local(Stack *stack);
//==========

//==========
void Recover_Stack(Stack *stack);
//==========
