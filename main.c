#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "funcs_pub.h"
#include "assertion.h"

int main ()
{
    m_stack *a = m_stack_init();
    FILE *log = fopen("log.out", "w");
    for (int i = 0; i < 10000; i++) {
        m_stack_push(a, i);
        m_stack_push(a, 2);
        m_stack_pop(a);
        
    }
    m_stack_clear(a);
    m_stack_dump(a, log);
    // for(int i = 0; i < 10000; i++)
    //     printf("%f\n", m_stack_pop(a));
    m_stack_destrct(a);
    return 0;
}