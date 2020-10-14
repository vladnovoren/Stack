#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define     default_stack_size_value 0
#define default_stack_capacity_value 100
#define         default_canary_value 0xDEADDED

#define hash_const 23
#define   hash_mod (int)(1e9 + 7)

typedef int stack_type;
#define int_stack

#ifdef int_stack
    #define poison 0xDEADDED
#endif

#ifdef float_stack
    #define poison -9,888075496
#endif

#ifdef double_stack
    #define poison 0xDEADDED
#endif

#ifdef long_long_stack
    #define poison 0xDEADDED
#endif

#ifdef string_stack
    #define poison NULL
#endif

typedef struct Stack{
    int left_canary;

    size_t size;

    size_t capacity;

    stack_type *data;

    struct Stack *copy;

    int hash;

    int right_canary;
} Stack;

Stack Stack_Init();

void Enlarge_Stack(Stack *stack);

void Reduce_Stack(Stack *stack);

void Resize_Stack(Stack *stack);

void Push(Stack *stack, stack_type value);

void Empty_Stack();

stack_type Pop(Stack *stack);

stack_type Back(Stack *stack);

void Clear(Stack *stack);

void Insert_Poison(Stack *stack);

int Hash_Formula(int first, int second);

int Count_Stack_Hash(Stack *stack);

int Size(Stack *stack);

int Capacity(Stack *stack);

void Copy_Stack(Stack *stack);

void Recover_Stack(Stack *stack);