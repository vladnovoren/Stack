#ifndef FUNCS_PRV_H
#define FUNCS_PRV_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "funcs_pub.h"


//private funcs & consts.

struct m_stack {
    double left_cnry;

    size_t size;

    size_t cpcty;

    m_stack_type *data;

    int data_ptr_hash;

    int hash;

    double right_cnry;
};

static const m_stack_type STACK_POISON   = NAN;
static const size_t DFLT_STACK_SIZE_VAL  = 0;
static const size_t DFLT_STACK_CPCTY_VAL = 8;
static const size_t MAX_STACK_SIZE_VAL   = 100000000;
static const double DFLT_STACK_CNRY_VAL  = 0xBEDADEDA;
static const size_t CNRY_SIZE            = sizeof(double);
static const int hash_const              = 23;
static const int hash_mod                = 1000000007;


long long minimum(long long first, long long second);

long long maximum(long long first, long long second);

void set_deflts(m_stack *cur_stack);

void resize(m_stack *cur_stack, size_t new_size);

void ins_poison(m_stack *cur_stack);

int count_data_ptr_hash(m_stack *cur_stack);

int count_hash(m_stack *cur_stack);

int hash_formula(int prev, int cur);

//=======================


#endif /* "funcs_prv.h" */