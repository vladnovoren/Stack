#include "assertion.h"
#include "funcs_prv.h"
#include "locale.h"

int m_stack_dump(m_stack *cur_stack, FILE *log)
{
    assert(cur_stack != NULL);
    assert(log != NULL);

    fprintf(log, "\n\n##########================ m_stack dump ================##########\n\n");
    fprintf(log, "the angle quotes contain the address of the variable.\n\n");
    fprintf(log, "verifier messages:\n");
    fprintf(log, "==================================================================\n");
    int ans = m_stack_verifier(cur_stack, log);
    if (ans == 0)
        fprintf(log, "m_stack is OK.\n");
    fprintf(log, "==================================================================\n\n");

    fprintf(log, "main m_stack characteristics:\n");
    fprintf(log, "==================================================================\n");
    fprintf(log, "m_stack      <%p>\n", cur_stack);

    fprintf(log, "left canary  <%p> = %llu\n", &cur_stack->left_cnry, cur_stack->left_cnry);
    fprintf(log, "size         <%p> = %zu\n", &cur_stack->size, cur_stack->size);
    fprintf(log, "capacity     <%p> = %zu\n", &cur_stack->cpcty, cur_stack->cpcty);
    fprintf(log, "right canary <%p> = %llu\n", &cur_stack->left_cnry, cur_stack->left_cnry);
    fprintf(log, "==================================================================\n\n");
    
    fprintf(log, "\noutput of m_stack data array:\n");
    fprintf(log, "==================================================================\n");
    for (int pos = 0; pos < cur_stack->cpcty; pos++) {
        if(cur_stack->data + pos == NULL) {
            printf("Pointer is NULL!!!\n");
            continue;
        }
        if (cur_stack->data[pos] == STACK_POISON) {
            fprintf(log, "poison !!!: ");
        } else {
            fprintf(log, "non-poison: ");
        }

        fprintf(log, "data[%05d] <%p> = ", pos, cur_stack->data + pos);
        fprintf(log, PRINT_FLAG, cur_stack->data[pos]);
        fprintf(log, "\n");
    } 
    fprintf(log, "##########==============================================##########\n\n");

    return ans;
}

int m_stack_verifier(m_stack *cur_stack, FILE *log)
{
    assert(log != NULL);

    int ans = 0;

    if (cur_stack == NULL) {
        fprintf(log, "verifier reported error code %d: stack pointer is NULL!!!\n", STACK_NULL);
        ans = 1;
    }

    if (cur_stack->copy == NULL) {
        fprintf(log, "verifier reported error code %d: stack_copy pointer is NULL!!!\n", STACK_COPY_NULL);
        ans = 1;
    }

    if (cur_stack->left_cnry != DFLT_STACK_CNRY_VAL) {
        fprintf(log, "verifier reported error code %d: left canary dead!!!\n", STACK_LEFT_CANARY_DEAD);
        ans = 1;
    }

    if (cur_stack->right_cnry != DFLT_STACK_CNRY_VAL) {
        fprintf(log, "verifier reported error code %d: right canary dead!!!\n", STACK_RIGHT_CANARY_DEAD);
        ans = 1;
    }

    if (cur_stack->size > cur_stack->cpcty) {
        fprintf(log, "verifier reported error code %d: size > capacity!!!\n", STACK_OVERSIZE);
        ans = 1;
    }
    
    for (int pos = cur_stack->size; pos < cur_stack->cpcty; pos++) {
        if (cur_stack->data[pos] != STACK_POISON) {
            fprintf(log, "verifier reported error code %d: poison got spilled!!!\n", STACK_POISON_SPILLED);
            ans = 1;
        }
        break;
    }

    return ans;
}