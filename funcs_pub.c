#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

//include declarations of all functions.
#include "funcs_prv.h"

//description of public functions

m_stack *m_stack_init()
{
    m_stack *new_stack = calloc(1, sizeof(m_stack));
    assert(new_stack != NULL);

    new_stack->copy  = calloc(1, sizeof(m_stack));
    assert(new_stack->copy != NULL);

    m_stack_set_deflts(new_stack);
    m_stack_ins_poison(new_stack);

    return new_stack;
}

size_t m_stack_size(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    return cur_stack->size;
}

m_stack_type m_stack_back(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    if (cur_stack->size == 0) {
        printf("Stack is empty!\n");

        return 0;
    }

    return cur_stack->data[cur_stack->size - 1];
}

void m_stack_push(m_stack *cur_stack, m_stack_type value)
{
    assert(cur_stack != NULL);

    cur_stack->size++;
    cur_stack->copy->size++;

    m_stack_resize(cur_stack);
    m_stack_ins_poison(cur_stack);

    cur_stack->data[cur_stack->size - 1] = value;
    cur_stack->copy->data[cur_stack->size - 1] = value;
}

m_stack_type m_stack_pop(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    if (cur_stack->size == 0) {
        printf("Stack is empty\n");

        return 0;
    }

    m_stack_type temp = cur_stack->data[cur_stack->size - 1];
    cur_stack->data[cur_stack->size - 1] = STACK_POISON;
    cur_stack->copy->data[cur_stack->size - 1] = STACK_POISON;

    cur_stack->size--;
    cur_stack->copy->size--;
    m_stack_resize(cur_stack);

    return temp;
}

void m_stack_clear(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    m_stack_clear_lcl(cur_stack->copy);
    m_stack_clear_lcl(cur_stack);

    cur_stack = m_stack_init();
}

void  m_stack_destrct(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    m_stack_clear_lcl(cur_stack->copy);
    m_stack_clear_lcl(cur_stack);
}

//==================================