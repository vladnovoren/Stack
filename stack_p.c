#include "stack_p.h"

//description of private functions

static void Enlarge_Stack(Stack *stack){
    assert(stack != NULL);
    
    Enlarge_Stack_Local(stack);
    Enlarge_Stack_Local(stack->copy);
}

static void Enlarge_Stack_Local(Stack *stack){
    assert(stack != NULL);
    
    stack->cpcty *= 2;
    if(realloc(stack->data, stack->cpcty * sizeof(stack_type)) == NULL)
        printf("balda\n");

    Insert_Poison_Local(stack);
}

static void Reduce_Stack(Stack *stack){
    assert(stack != NULL);
    
    Reduce_Stack_Local(stack);
    Reduce_Stack_Local(stack->copy);
}

static void Reduce_Stack_Local(Stack *stack){
    assert(stack != NULL);

    stack->cpcty /= 2;
    if(realloc(stack->data, stack->cpcty * sizeof(stack_type)) == NULL)
        printf("balda\n");
}

static int Resize_Stack(Stack *stack){
    assert(stack != NULL);

    Resize_Stack_Local(stack);
    return Resize_Stack_Local(stack->copy);
}

static int Resize_Stack_Local(Stack *stack){
    assert(stack != NULL);

    if(4 * stack->size < stack->cpcty){
        Reduce_Stack_Local(stack);
        return -1;
    }
    if(stack->size >= stack->cpcty){
        Enlarge_Stack_Local(stack);
        return 1;
    }
    return 1;
}

static void Insert_Poison(Stack *stack){
    assert(stack != NULL);

    Insert_Poison_Local(stack);
    Insert_Poison_Local(stack->copy);
}

static void Insert_Poison_Local(Stack *stack){
    assert(stack != NULL);

    for(int pos = stack->size; pos < stack->cpcty; pos++)
        stack->data[pos] = STACK_POISON;
}

static void Copy_Stack(Stack *stack){
    assert(stack != NULL);

    stack->copy->left_cnry = stack->left_cnry;
    stack->copy->size = stack->size;
    stack->copy->cpcty = stack->cpcty;

    stack->copy->data = (stack_type *)calloc(stack->cpcty, sizeof(stack_type));
    for(int pos = 0; pos < stack->cpcty; pos++)
        stack->copy->data[pos] = stack->data[pos];

    stack->copy->right_cnry = stack->right_cnry;
}

static void Recovery_Stack(Stack *stack){
    assert(stack != NULL);

    stack->size = stack->copy->size;
    stack->cpcty = stack->copy->cpcty;
    Resize_Stack_Local(stack);
    
    for(int pos = 0; pos < stack->cpcty; pos++)
        stack->data[pos] = stack->copy->data[pos];
}

//==================================

void Clear_Stack_Local(Stack *stack){
    assert(stack != NULL);

    free(stack->data);
    free(stack);
}

void Set_Defaults(Stack *stack){
    assert(stack != NULL);

    stack->left_cnry  = DFLT_STACK_CNRY_VAL;

    stack->size       = DFLT_STACK_SIZE_VAL;
    stack->cpcty      = DFLT_STACK_CPCTY_VAL;
    stack->data       = (stack_type)calloc(DFLT_STACK_CPCTY_VAL, sizeof(stack_type));

    stack->right_cnry = DFLT_STACK_CNRY_VAL;
}