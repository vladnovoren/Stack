#include "stack_p.h"

/*static*/ void Dump_Stack(Stack *stack){
    assert(stack != NULL);
    
    printf("\n===Stack dump===\n\n");

    printf("В кавычках указывается адрес переменной.\n");
    printf("Stack <%p>\n", stack);

    printf("size <%p> = %zu\n", &stack->size, stack->size);
    printf("cpcty <%p> = %zu\n", &stack->cpcty, stack->cpcty);
    
    for(int pos = 0; pos < stack->cpcty; pos++){
        printf("data[%05d] <%p> = ", pos, stack->data + pos);

        printf(print_flag, stack->data[pos]);

        if(stack->data[pos] == STACK_POISON && pos >= stack->size)
            printf("\t - poison!!!!!\n");
        else
            printf("\t - non-poison\n");
    } 
    printf("\n================\n");
}