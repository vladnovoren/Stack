#ifndef ASSERTION_H
#define ASSERTION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

//include declaration of all functions.

#include "funcs_prv.h"


void m_stack_dump(m_stack *stack, FILE *log);

int m_stack_verifier(m_stack *stack, char *file_name, int line_num);

typedef enum stack_status {
    STACK_ALRIGHT,
    STACK_NULL,
    STACK_DATA_NULL,
    STACK_LEFT_CANARY_DIED,
    STACK_RIGHT_CANARY_DIED,
    STACK_OVERFLOW,
    STACK_LEFT_DATA_CANARY_DIED,
    STACK_RIGHT_DATA_CANARY_DIED,
    STACK_WRONG_HASH,
    STACK_POISON_SPILLED
} stack_status;


#endif /* "assertion.h" */