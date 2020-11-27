#ifndef ASSERTION_H
#define ASSERTION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "funcs_pub.h"

void m_stack_dump(m_stack *stack, int is_valid_data);

void m_stack_verifier(m_stack *stack, char *file_name, const char *func_name, int line_num, int errors[11]);

static const int VALID_DATA   = 0;
static const int INVALID_DATA = 1;
static const int ERR_CNT      = 11;
static const int UNDEF_STATE  = -1;

typedef enum stack_status {
    STACK_ALRIGHT,
    STACK_NULL,
    STACK_DATA_NULL,
    STACK_LEFT_CANARY_DIED,
    STACK_RIGHT_CANARY_DIED,
    STACK_OVERFLOW,
    STACK_WRONG_DATA_PTR_HASH,
    STACK_LEFT_DATA_CANARY_DIED,
    STACK_RIGHT_DATA_CANARY_DIED,
    STACK_WRONG_DATA_HASH,
    STACK_POISON_SPILLED
} stack_status;


#endif /* "assertion.h" */