#ifndef FUNCS_PUB_H
#define FUNCS_PUB_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>


//include declaration of m_stack.
#include "stack_decl.h"


//==public funcs====

m_stack *m_stack_init();

size_t m_stack_size(m_stack *cur_stack);

m_stack_type m_stack_back(m_stack *cur_stack);

void m_stack_push(m_stack *cur_stack, m_stack_type value);

m_stack_type m_stack_pop(m_stack *cur_stack);

void m_stack_clear(m_stack *cur_stack);

void m_stack_destrct(m_stack *cur_stack);

//==================


#endif /* "funcs_pub.h" */