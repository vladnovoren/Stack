//
#ifndef STACK_DEF_H
    #define STACK_DEF_H
#endif
//
#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef STACK_DECL_H
    #include "stack_decl.h"
#endif

typedef struct Stack{

    int left_cnry;

    size_t size;    

    size_t cpcty;

    struct Stack *copy;

    stack_type *data;

    int right_cnry;
    
} Stack;