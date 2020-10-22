#ifndef FUNCS_PRV_H
#define FUNCS_PRV_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

//include definition of m_stack & declaration of public functions.
#include "stack_def.h"
#include "funcs_pub.h"


//private funcs & consts.

static const m_stack_type STACK_POISON              = 0xBADEDA;
static const int DFLT_STACK_SIZE_VAL                = 0;
static const int DFLT_STACK_CPCTY_VAL               = 100;
static const unsigned long long DFLT_STACK_CNRY_VAL = 0xBEDADEDA;

void m_stack_set_deflts(m_stack *cur_stack);
void m_stack_set_deflts_lcl(m_stack *cur_stack);

void m_stack_enlarge(m_stack *cur_stack);
void m_stack_enlarge_lcl(m_stack *cur_stack);

void m_stack_reduce(m_stack *cur_stack);
void m_stack_reduce_lcl(m_stack *cur_stack);

int m_stack_resize(m_stack *cur_stack);
int m_stack_resize_lcl (m_stack *cur_stack);

void m_stack_ins_poison(m_stack *cur_stack);
void m_stack_ins_poison_lcl(m_stack *cur_stack);

void m_stack_copy(m_stack *cur_stack); 

void m_stack_clear_lcl(m_stack *cDFLur_stack);

void m_stack_recover(m_stack *cur_stack);

//=======================


#endif /* "funcs_prv.h" */