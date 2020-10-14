#include "stack.h"

Stack Stack_Init(){
    Stack new;

    new.size     = default_stack_size_value;
    new.capacity = default_stack_capacity_value;
    new.data     = calloc(new.capacity, sizeof(stack_type));
    new.hash     = Count_Stack_Hash(&new);

    

    Insert_Poison(&new);
    Copy_Stack(&new);
    return new;
}

void Empty_Stack(){
    printf("error: stack is emptry\n");
}

void Enlarge_Stack(Stack *stack){
    stack->capacity *= 2;
    realloc(stack->data, stack->capacity);

    Insert_Poison(stack);
}

void Reduce_Stack(Stack *stack){
    stack->capacity /= 2;
    realloc(stack->data, stack->capacity);
}

void Resize_Stack(Stack *stack){
    if(4 * stack->size < stack->capacity)
        Reduce_Stack(stack);
    if(stack->size >= stack->capacity)
        Enlarge_Stack(stack);
}

void Push(Stack *stack, stack_type value){
    stack->size++;
    printf("123\n");
    Resize_Stack(stack);

    stack->data[stack->size - 1] = value;
}

stack_type Pop(Stack *stack){
    if(stack->size == 0){
        Empty_Stack();
        return 0;
    }

    stack_type temp = stack->data[stack->size - 1];
    stack->data[stack->size - 1] = poison;

    stack->size--;    
    Resize_Stack(stack);

    return temp;
}

int Size(Stack *stack){
    return stack->size;
}

int Capacity(Stack *stack){
    return stack->capacity;
}

stack_type Back(Stack *stack){
    if(stack->size == 0){
        Empty_Stack();
        return 0;
    }

    return stack->data[stack->size - 1];
}

void Insert_Poison(Stack *stack){
    for(int pos = stack->size; pos <= stack->capacity; pos++)
        stack->data[pos] = poison;
}

void Clear(Stack *stack){
    *stack = Stack_Init();
}

int Hash_Formula(int first, int second){
    return (first * second + hash_const) % hash_mod;
}

int Count_Stack_Hash(Stack *stack){
    int res = 1;
    
    for(char *pos = (char *)stack->data + sizeof(int); pos != (char *)stack->data + stack->capacity * sizeof(stack_type); pos++)
        res = Hash_Formula(res, (*pos));
    
    return res;
}

void Dump_Stack(Stack *stack){
    printf("Stack <%p>\n", stack);

    printf("size <%p> = %d\n", &stack->size, stack->size);
    printf("capacity <%p> = %d\n", &stack->capacity, stack->capacity);
    
    for(int pos = 0; pos < stack->capacity; pos++){
        printf("data[%d] <%p> = ", pos, stack->data + pos);

        #ifdef int_stack
            printf("%d", stack->data[pos]);
        #endif

        #ifdef float_stack
            printf("%f", stack->data[pos]);
        #endif

        #ifdef double_stack
            printf("%lg", stack->data[pos]);
        #endif

        #ifdef long_long_stack
            printf("%lld", stack->data[pos]);
        #endif
        #ifdef string_stack
            printf("%s", stack->data[pos]);
        #endif

        if(stack->data[pos] == poison)
            printf(" - poison!!!\n");
        else
            printf(" - non-poison\n");
    } 
}

void Copy_Stack(Stack *stack){
    stack->copy->size     = stack->size;
    stack->copy->capacity = stack->capacity;
    stack->copy->hash     = stack->hash;
    for(int pos = 0; pos < stack->capacity; pos++)
        stack->copy->data[pos] = stack->data[pos];
    stack->copy = NULL;
}

void Recovery_Stack(Stack *stack){
    stack->size = stack->copy->size;
    stack->capacity = stack->copy->capacity;
    stack->hash = stack->copy->hash;
    for(int pos = 0; pos < stack->copy->capacity; pos++)
        stack->data[pos] = stack->copy->data[pos];
}