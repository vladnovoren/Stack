#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "funcs_prv.h"
#include "assertion.h"

//description of public functions.

#ifdef DEBUG
    #define DEBUG_CHECK \
    { \
    FILE *log = fopen("stack_log.txt", "a"); \
    int ver_ret = m_stack_verifier(cur_stack, __FILE__, __LINE__); \
    if (ver_ret != 0) \
        fclose(log); \
        return ver_ret; \
    fclose(log); \
    }
#endif

#ifndef DEBUG_CHECK
    #define DEBUG_CHECK
#endif



m_stack *m_stack_init()
{
    m_stack *new_m_stack = (m_stack *)calloc(1, sizeof(m_stack));
    new_m_stack->data = NULL;
    set_deflts(new_m_stack);

    return new_m_stack;
}

size_t m_stack_size(m_stack *cur_stack)
{
    DEBUG_CHECK

    return cur_stack->size;
}

m_stack_type m_stack_back(m_stack *cur_stack)
{
    DEBUG_CHECK

    if (cur_stack->size == 0) {
        printf("Stack is empty!\n");

        return 1;
    }

    DEBUG_CHECK
    return cur_stack->data[cur_stack->size];
}

int m_stack_push(m_stack *cur_stack, m_stack_type value)
{
    DEBUG_CHECK

    cur_stack->size++;

    resize(cur_stack, cur_stack->size);

    cur_stack->data[cur_stack->size] = value;

    DEBUG_CHECK

    return 0;
}

m_stack_type m_stack_pop(m_stack *cur_stack)
{
    DEBUG_CHECK

    if (cur_stack->size == 0) {
        printf("Stack is empty\n");

        return 0;
    }

    m_stack_type temp = cur_stack->data[cur_stack->size];
    cur_stack->data[cur_stack->size] = STACK_POISON;
    cur_stack->size--;
    resize(cur_stack, cur_stack->size);

    DEBUG_CHECK

    return temp;
}

int m_stack_clear(m_stack *cur_stack)
{

    DEBUG_CHECK

    set_deflts(cur_stack);

    DEBUG_CHECK

    return 0;
}

int m_stack_destrct(m_stack *cur_stack)
{
    DEBUG_CHECK

    free(cur_stack->data);
    free(cur_stack);

    return 0;
}

//==================================