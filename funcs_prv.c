#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


//include declarations of all functions.
#include "funcs_prv.h"
#include "assertion.h"


//description of private functions.

long long minimum(long long first, long long second)
{
    return (first < second) ? first : second;
}

long long maximum(long long first, long long second)
{
    return (first > second) ? first : second;
}



int set_deflts(m_stack *cur_stack)
{
    cur_stack->left_cnry  = DFLT_STACK_CNRY_VAL;

    cur_stack->size       = DFLT_STACK_SIZE_VAL;
    cur_stack->cpcty      = DFLT_STACK_CPCTY_VAL;

    free(cur_stack->data);
    m_stack_type *tmp = (m_stack_type *)calloc(2 * CNRY_SIZE + DFLT_STACK_CPCTY_VAL, sizeof(m_stack_type));
    if(tmp == NULL)
        return 2;
    else
        cur_stack->data = tmp;
    
    cur_stack->data[0] = DFLT_STACK_CNRY_VAL;
    cur_stack->data[cur_stack->cpcty + 1] = DFLT_STACK_CNRY_VAL;

    ins_poison(cur_stack);

    count_hash(cur_stack);

    cur_stack->right_cnry = DFLT_STACK_CNRY_VAL;

    return 0;
}

int resize(m_stack *cur_stack, size_t new_size)
{
    assert(cur_stack != NULL);

    if(new_size > MAX_STACK_SIZE_VAL)
        return 1;
    
    size_t new_cpcty = cur_stack->cpcty;
    if (cur_stack->cpcty > new_size * 4) {
        new_cpcty = cur_stack->cpcty / 2;
    } else {
        if (cur_stack->cpcty < new_size) {
            new_cpcty = new_size * 2;
        }
    }

    cur_stack->cpcty = new_cpcty;
    m_stack_type *tmp = (m_stack_type *)realloc(cur_stack->data, new_cpcty * sizeof(m_stack_type) + 2 * CNRY_SIZE);
    if(tmp == NULL)
        return 2;
    else {
        cur_stack->data = tmp;
        cur_stack->data[0] = DFLT_STACK_CNRY_VAL;
        cur_stack->data[cur_stack->cpcty + 1] = DFLT_STACK_CNRY_VAL;
        ins_poison(cur_stack);
    }

    return 0;
}

void ins_poison(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    for (int pos = cur_stack->size; pos < cur_stack->cpcty; pos++)
        cur_stack->data[pos + 1] = STACK_POISON;
}

int hash_formula(int prev, int cur)
{
    return ((prev + hash_const) % hash_mod) * (cur % hash_mod) % hash_mod;
}

int count_hash(m_stack *cur_stack)
{
    assert(cur_stack != NULL);

    char *first = (char *)(cur_stack->data + 1);
    char *last = (char *)(cur_stack->data + cur_stack->size + 1);

    int cur = 1;

    for (char *ptr = first; ptr != last; ptr++)
        cur = hash_formula((int)*ptr, cur);
    
    cur_stack->hash = cur;
    return cur;
}

//=================================
