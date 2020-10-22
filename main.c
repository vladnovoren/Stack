#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "funcs_pub.h"
#include "assertion.h"

int main ()
{
    m_stack *a;
    a = m_stack_init();
    FILE *log = fopen("log.out", "w");
    for (int pos = 0; pos < 100; pos++) {
        m_stack_push(a, 1);
        fprintf(log, "original:");
        m_stack_dump(a, log);
        fprintf(log, "copy:");
        m_stack_dump(a->copy, log);
    }

    m_stack_destrct(a);

    return 0;
}