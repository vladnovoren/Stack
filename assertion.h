#ifndef ASSERTION_H
#define ASSERTION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

//include declaration of all functions.

#include "funcs_prv.h"


int m_stack_dump(m_stack *stack, FILE *log);

int m_stack_verifier(m_stack *stack, FILE *log);

typedef enum stack_status {
    STACK_ALRIGHT,
    STACK_NULL,
    STACK_COPY_NULL,
    STACK_LEFT_CANARY_DEAD,
    STACK_RIGHT_CANARY_DEAD,
    STACK_OVERSIZE,
    STACK_POISON_SPILLED
} stack_status;


#endif /* "assertion.h" */