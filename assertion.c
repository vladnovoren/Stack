#include "assertion.h"
#include "funcs_prv.h"
#include "locale.h"

#define LOG_PRINT \
fprintf(log, "file: %s, line: %d.\nverifier returned error code ", file_name, line_num);

void m_stack_dump(m_stack *cur_stack, FILE *log)
{
    assert(cur_stack != NULL);
    assert(log != NULL);

    fprintf(log, "\n\n##########================ m_stack dump ================##########\n\n");
    fprintf(log, "the angle quotes contain the address of the variable.\n\n");
    fprintf(log, "main m_stack characteristics:\n");
    fprintf(log, "==================================================================\n");
    fprintf(log, "m_stack      <%p>\n", cur_stack);

    fprintf(log, "left canary  <%p> = %f\n", &cur_stack->left_cnry, cur_stack->left_cnry);
    fprintf(log, "size         <%p> = %zu\n", &cur_stack->size, cur_stack->size);
    fprintf(log, "capacity     <%p> = %zu\n", &cur_stack->cpcty, cur_stack->cpcty);
    fprintf(log, "hash         <%p> = %d\n", &cur_stack->hash, cur_stack->hash);
    fprintf(log, "right canary <%p> = %f\n", &cur_stack->left_cnry, cur_stack->left_cnry);
    fprintf(log, "==================================================================\n\n");
    
    fprintf(log, "\noutput of m_stack data array:\n");
    fprintf(log, "==================================================================\n");

    for (int pos = 0; pos <= cur_stack->cpcty + 1; pos++) {
        if(pos == 0)
            fprintf(log, "Left data canary:\n");
        if(pos == cur_stack->cpcty + 1)
            fprintf(log, "\nRight data canary:\n");
        if (cur_stack->data + pos == NULL) {
            fprintf(log, "Pointer is NULL!!!\n");
            continue;
        }
        if (isnan(cur_stack->data[pos])) {
            fprintf(log, "poison !!!: ");
        } else {
            fprintf(log, "non-poison: ");
        }

        fprintf(log, "data[%05d] <%p> = ", pos, cur_stack->data + pos);
        fprintf(log, PRINT_FLAG, cur_stack->data[pos]);
        fprintf(log, "\n");
        if(pos == 0)
            fprintf(log, "\n");
    } 
    fprintf(log, "##########==============================================##########\n\n");
}

int m_stack_verifier(m_stack *cur_stack, char *file_name, int line_num)
{
    FILE *log = stdout;

    if (cur_stack == NULL) {
        LOG_PRINT
        fprintf(log, "%d: pointer to m_stack is NULL.\n", STACK_NULL);
        return STACK_NULL;
    }

    if (cur_stack->data == NULL) {
        LOG_PRINT
        fprintf(log, "%d: pointer to m_stack->data is NULL.\n", STACK_DATA_NULL);
        m_stack_dump(cur_stack, log);
        return STACK_DATA_NULL;
    }

    if (cur_stack->left_cnry != DFLT_STACK_CNRY_VAL) {
        LOG_PRINT
        fprintf(log, "%d: left canary died.\n", STACK_LEFT_CANARY_DIED);
        
        m_stack_dump(cur_stack, log);
        return STACK_LEFT_CANARY_DIED;
    }

    if (cur_stack->left_cnry != DFLT_STACK_CNRY_VAL) {
        LOG_PRINT
        fprintf(log, "%d: right canary died.\n", STACK_RIGHT_CANARY_DIED);
        m_stack_dump(cur_stack, log);
        return STACK_RIGHT_CANARY_DIED;
    }

    if(cur_stack->size > MAX_STACK_SIZE_VAL || cur_stack->size > cur_stack->cpcty || cur_stack->size < 0) {
        LOG_PRINT
        fprintf(log, "%d: m_stack overflow.\n", STACK_OVERFLOW);
        m_stack_dump(cur_stack, log);
        return STACK_OVERFLOW;
    }

    if (cur_stack->data[0] != DFLT_STACK_CNRY_VAL) {
        LOG_PRINT
        fprintf(log, "%d: left data canary died.\n", STACK_LEFT_DATA_CANARY_DIED);
        fprintf(log, "ebanator %f norm %f\n", cur_stack->data[0], DFLT_STACK_CNRY_VAL);
        m_stack_dump(cur_stack, log);
        return STACK_LEFT_DATA_CANARY_DIED;
    }

    if (cur_stack->data[cur_stack->cpcty + 1] != DFLT_STACK_CNRY_VAL) {
        LOG_PRINT
        fprintf(log, "%d: right data canary died.\n", STACK_RIGHT_DATA_CANARY_DIED);
        m_stack_dump(cur_stack, log);
        return STACK_RIGHT_DATA_CANARY_DIED;
    }

    if (count_hash(cur_stack) != cur_stack->hash) {
        LOG_PRINT
        fprintf(log, "%d: hash is wrong, data corrupted.\n", STACK_WRONG_HASH);
        m_stack_dump(cur_stack, log);
        return STACK_WRONG_HASH;
    }

    m_stack_type *first = cur_stack->data + cur_stack->size + 1;
    m_stack_type *last  = cur_stack->data + cur_stack->cpcty + 1;
    for (m_stack_type *ptr = first; ptr != last; ptr++) {
        if (!isnan(*ptr)) {
            LOG_PRINT;
            fprintf(log, "%d: poison got spilled.\n", STACK_POISON_SPILLED);
            m_stack_dump(cur_stack, log);
            return STACK_POISON_SPILLED;
        }
    }

    return STACK_ALRIGHT;
}