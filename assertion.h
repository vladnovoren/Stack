#ifndef ASSERTION_H
    #define ASSERTION_H
#endif

#ifndef FUNCS_PRV_H
    #include "funcs_prv.h"
#endif

int Dump_Stack(Stack *stack, FILE *log);

int Verifier(Stack *stack, FILE *log);

typedef enum status{
    STACK_ALRIGHT,
    STACK_NULL,
    STACK_COPY_NULL,
    STACK_LEFT_CANARY_DEAD,
    STACK_RIGHT_CANARY_DEAD,
    STACK_OVERSIZE,
    STACK_POISON_OK
} status;