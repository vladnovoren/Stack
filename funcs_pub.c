#ifndef FUNCS_PRV_H
    #include "funcs_prv.h"
#endif

#ifndef ASSERTION_H
    #include "assertion.h"
#endif



//description of public functions

Stack *Init_Stack(){
    Stack *new = calloc(1, sizeof(Stack));
    assert(new != NULL);

    new->copy  = calloc(1, sizeof(Stack));
    assert(new->copy != NULL);

    Set_Defaults(new);

    Insert_Poison(new);

    printf("Init:\n");

    return new;
}

size_t Size(Stack *stack){
    assert(stack != NULL);

    return stack->size;
}

stack_type Back(Stack *stack){
    assert(stack != NULL);

    if(stack->size == 0){
        printf("Stack is empty!\n");

        return 0;
    }

    return stack->data[stack->size - 1];
}

void Push(Stack *stack, stack_type value){
    assert(stack != NULL);

    stack->size++;
    stack->copy->size++;
    Resize_Stack(stack);
    Insert_Poison(stack);

    stack->data[stack->size - 1] = value;
    stack->copy->data[stack->copy->size - 1] = value;

    printf("Push:\n");
}

stack_type Pop(Stack *stack){
    assert(stack != NULL);

    if(stack->size == 0){
        printf("Stack is empty\n");

        return 0;
    }

    stack_type temp = stack->data[stack->size - 1];
    stack->data[stack->size - 1] = STACK_POISON;
    stack->copy->data[stack->copy->size - 1] = STACK_POISON;

    stack->size--;
    stack->copy->size--;
    Resize_Stack(stack);

    return temp;
}

void Clear_Stack(Stack *stack){
    assert(stack != NULL);

    Clear_Stack_Local(stack->copy);
    Clear_Stack_Local(stack);

    stack = Init_Stack();
}

void Destruct_Stack(Stack *stack){
    assert(stack != NULL);

    Clear_Stack_Local(stack->copy);
    Clear_Stack_Local(stack);
}

//==================================