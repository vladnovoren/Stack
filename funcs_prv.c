#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


//include declarations of all functions.
#include "funcs_prv.h"


//description of private functions

//==========
void m_stack_set_deflts(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    m_stack_set_deflts_lcl(cur_stack);
    m_stack_set_deflts_lcl(cur_stack->copy);
}

//
void m_stack_set_deflts_lcl(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    cur_stack->left_cnry  = DFLT_STACK_CNRY_VAL;

    cur_stack->size       = DFLT_STACK_SIZE_VAL;
    cur_stack->cpcty      = DFLT_STACK_CPCTY_VAL;

    free(cur_stack->data);
    cur_stack->data       = (m_stack_type *)calloc(DFLT_STACK_CPCTY_VAL, sizeof(m_stack_type));

    cur_stack->right_cnry = DFLT_STACK_CNRY_VAL;
}
//==========


//==========
void m_stack_enlarge(m_stack *cur_stack)
{
    assert(cur_stack != NULL);
    
    m_stack_enlarge_lcl(cur_stack);
    m_stack_enlarge_lcl(cur_stack->copy);
}

//
void m_stack_enlarge_lcl(m_stack *cur_stack)
{
    assert(cur_stack != NULL);
    
    printf("zalupa old: %lu\n", cur_stack->cpcty * sizeof(m_stack_type));
    cur_stack->cpcty *= 2;

    printf("zalupa new: %lu\n", cur_stack->cpcty * sizeof(m_stack_type));
    cur_stack->data = (m_stack_type *)realloc(cur_stack->data, cur_stack->cpcty * sizeof(m_stack_type));
    //assert(tmp);

    m_stack_ins_poison_lcl(cur_stack);
}
//==========


//==========
void m_stack_reduce(m_stack *cur_stack)
{
    assert(cur_stack != NULL);
    
    m_stack_reduce_lcl(cur_stack);
    m_stack_reduce_lcl(cur_stack->copy);
}

//
void m_stack_reduce_lcl(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    cur_stack->cpcty /= 2;
    cur_stack->size = (cur_stack->size > cur_stack->cpcty) ? cur_stack->cpcty : cur_stack->size;

    cur_stack->data = (m_stack_type *)realloc(cur_stack->data, cur_stack->cpcty * sizeof(m_stack_type));

    m_stack_ins_poison_lcl(cur_stack);
}
//=========


//=========
int m_stack_resize(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    m_stack_resize_lcl(cur_stack);
    return m_stack_resize_lcl(cur_stack->copy);
}

//
int m_stack_resize_lcl(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    if (4 * cur_stack->size < cur_stack->cpcty) {
        m_stack_reduce_lcl(cur_stack);
        return -1;
    }
    if (cur_stack->size >= cur_stack->cpcty) {
        m_stack_enlarge_lcl(cur_stack);
        return 1;
    }
    return 1;
}
//==========


//==========
void m_stack_ins_poison(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    m_stack_ins_poison_lcl(cur_stack);
    m_stack_ins_poison_lcl(cur_stack->copy);
}

//
void m_stack_ins_poison_lcl(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    for (int pos = cur_stack->size; pos < cur_stack->cpcty; pos++)
        cur_stack->data[pos] = STACK_POISON;
}
//==========


//==========
void m_stack_copy(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    cur_stack->copy->left_cnry = cur_stack->left_cnry;
    cur_stack->copy->size = cur_stack->size;
    cur_stack->copy->cpcty = cur_stack->cpcty;

    cur_stack->copy->data = (m_stack_type *)calloc(cur_stack->cpcty, sizeof (m_stack_type));
    for (int pos = 0; pos < cur_stack->cpcty; pos++)
        cur_stack->copy->data[pos] = cur_stack->data[pos];

    cur_stack->copy->right_cnry = cur_stack->right_cnry;
}
//==========


//==========
void m_stack_clear_lcl(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    free(cur_stack->data);
    free(cur_stack);
}
//==========


//==========
void m_stack_recover(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    cur_stack->size = cur_stack->copy->size;
    cur_stack->cpcty = cur_stack->copy->cpcty;
    m_stack_resize_lcl(cur_stack);
    
    for (int pos = 0; pos < cur_stack->cpcty; pos++)
        cur_stack->data[pos] = cur_stack->copy->data[pos];
}
//==========