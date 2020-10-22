#ifndef STACK_DEF_H
#define STACK_DEF_H


#include <stdio.h>
#include <stdlib.h>


//include declaration of m_stack.
#include "stack_decl.h"


typedef struct m_stack {
    unsigned long long left_cnry;

    size_t size;

    size_t cpcty;

    struct m_stack *copy;

    m_stack_type *data;

    unsigned long long right_cnry;
} m_stack;


#endif /* "stack_def.h" */