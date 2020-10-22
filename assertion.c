#include "assertion.h"
#include "locale.h"

int Dump_Stack(Stack *stack, FILE *log){
    assert(stack != NULL);
    assert(log != NULL);

    fprintf(log, "\n===Stack dump===\n\n");

    fprintf(log, "В кавычках указывается адрес переменной.\n");
    fprintf(log, "Stack <%p>\n", stack);

    fprintf(log, "size <%p> = %zu\n", &stack->size, stack->size);
    fprintf(log, "cpcty <%p> = %zu\n", &stack->cpcty, stack->cpcty);
    
    for(int pos = 0; pos < stack->cpcty; pos++){
        fprintf(log, "data[%05d] <%p> = ", pos, stack->data + pos);

        fprintf(log, PRINT_FLAG, stack->data[pos]);

        if(stack->data[pos] == STACK_POISON && pos >= stack->size)
            fprintf(log, "\t - poison!!!!!\n");
        else
            fprintf(log, "\t - non-poison\n");
    } 
    fprintf(log, "\n================\n");


}

int Verifier(Stack *stack, FILE *log){
    assert(log != NULL);

    if(stack == NULL){
        fprintf(log, "verifier reported error code %d: stack pointer is NULL\n", STACK_NULL);
    }

    if(stack->copy == NULL){
        fprintf(log, "verifier reported error code %d: stack_copy pointer is NULL\n", STACK_COPY_NULL);
    }

    if(stack->size > stack->cpcty){
        fprintf(log, "verifier reported error code %d: size > capacity\n", STACK_OVERSIZE);
    }
    
}