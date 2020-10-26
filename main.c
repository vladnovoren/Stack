#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "funcs_pub.h"

int main ()
{
    m_stack *a;
    a = m_stack_init();
    for(int i = 0; i < 10000; i++) 
        m_stack_push(a, i);
    return 0;
}