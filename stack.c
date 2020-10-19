#include "stack_p.h"


//description of public functions

void Stack_Init(Stack *new_stack){
    new_stack->right_canary = new_stack->left_canary = DEFAULT_STACK_CANARY_VALUE;
    
    new_stack->size     = DEFAULT_STACK_SIZE_VALUE;
    new_stack->capacity = DEFAULT_STACK_CAPACITY_VALUE;
    new_stack->data     = (stack_type *)calloc(new_stack->capacity, sizeof(stack_type));

    new_stack->copy->right_canary = new_stack->copy->left_canary = DEFAULT_STACK_CANARY_VALUE;
    
    new_stack->copy->size     = DEFAULT_STACK_SIZE_VALUE;
    new_stack->copy->capacity = DEFAULT_STACK_CAPACITY_VALUE;
    new_stack->copy->data     = (stack_type *)calloc(new_stack->capacity, sizeof(stack_type));
    new_stack->copy->copy = new_stack;

    Insert_Poison(new_stack);
}

int Size(Stack *stack){
    return stack->size;
}

stack_type Back(Stack *stack){
    if(stack->size == 0){
        return 0;
    }

    return stack->data[stack->size - 1];
}

void Push(Stack *stack, stack_type value){
    stack->size++;
    stack->copy->size++;
    Resize_Stack(stack);
    Insert_STACK_POISON(stack);

    stack->data[stack->size - 1] = value;
}

stack_type Pop(Stack *stack){
    if(stack->size == 0){
        Empty_Stack();
        return 0;
    }

    stack_type temp = stack->data[stack->size - 1];
    stack->data[stack->size - 1] = STACK_POISON;

    stack->size--;    
    Resize_Stack(stack);
    Copy_Stack(stack);
    return temp;
}

void Clear(Stack *stack){
    *stack = Stack_Init();
}

//==================================


//description of private functions

static void Enlarge_Stack(Stack *stack){
    stack->capacity *= 2;
    realloc(stack->data, stack->capacity);

    Insert_Poison(stack);
}

static void Reduce_Stack(Stack *stack){
    stack->capacity /= 2;
    realloc(stack->data, stack->capacity);
}

static int Resize_Stack(Stack *stack){
    if(4 * stack->size < stack->capacity){
        Reduce_Stack(stack);
        return -1;
    }
    if(stack->size >= stack->capacity){
        Enlarge_Stack(stack);
        return 1;
    }
}

static void Insert_Poison(Stack *stack){
    for(int pos = stack->size; pos < stack->capacity; pos++)
        stack->data[pos] = STACK_POISON;
}

static void Copy_Stack(Stack *stack){
    stack->left_canary = stack->copy.left_canary;
    stack->copy.size = stack->size;
    stack->copy.capacity = stack->capacity;

    stack->copy.data = (stack_type *)calloc(stack->capacity, sizeof(stack_type));
    for(int pos = 0; pos < stack->capacity; pos++)
        stack->copy.data[pos] = stack->data[pos];

    stack->right_canary = stack->copy.right_canary;
}

static void Recovery_Stack(Stack *stack){
    stack->size = stack->copy.size;
    stack->capacity = stack->copy.capacity;
    Resize_Stack(stack);

    for(int pos = 0; pos < stack->capacity; pos++)
        stack->data[pos] = stack->copy.data[pos];
}

static void Dump_Stack(Stack *stack){
    printf("\n===Stack dump===\n\n");
    printf("В кавычках указывается адрес переменной.\n");
    printf("Stack <%p>\n", stack);

    printf("size <%p> = %zu\n", &stack->size, stack->size);
    printf("capacity <%p> = %zu\n", &stack->capacity, stack->capacity);
    
    for(int pos = 0; pos < stack->capacity; pos++){
        printf("data[%d] <%p> = ", pos, stack->data + pos);

        printf(print_flag, stack->data[pos]);

        if(stack->data[pos] == STACK_POISON && pos >= stack->size)
            printf(" - STACK_POISON!!!\n");
        else
            printf(" - non-STACK_POISON\n");
    } 
    printf("\n================\n");
}

//==================================