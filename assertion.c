#include "assertion.h"
#include "funcs_prv.h"
#include "locale.h"

#define LOG_PRINT(err_code) \
printf("file: %s, line: %d - verifier returned error code %d.\ncheck \"stack_log.txt\" to see stack dump.\n\n", file_name, line_num, err_code); \
fprintf(log, "file: %s, line: %d - verifier returned error code ", file_name, line_num);

void m_stack_dump(m_stack *cur_stack, int is_valid_data)
{
    assert(cur_stack != NULL);
    
    FILE *log = fopen("stack_log.txt", "a");

    fprintf(log, "\n\n##########================ m_stack dump ================##########\n\n");
    fprintf(log, "the angle quotes contain the address of the variable.\n\n");
    fprintf(log, "main m_stack characteristics:\n");
    fprintf(log, "==================================================================\n");
    fprintf(log, "m_stack           <%p>\n", cur_stack);

    fprintf(log, "left canary       <%p> = %lf - ", &cur_stack->left_cnry, cur_stack->left_cnry);
    if (cur_stack->left_cnry == DFLT_STACK_CNRY_VAL)
        fprintf(log, "ALIVE\n");
    else
        fprintf(log, "DEAD!\n");
    fprintf(log, "size              <%p> = %zu\n", &cur_stack->size, cur_stack->size);
    fprintf(log, "capacity          <%p> = %zu\n", &cur_stack->cpcty, cur_stack->cpcty);
    fprintf(log, "data pointer hash <%p> = %d\n", &cur_stack->data_ptr_hash, cur_stack->data_ptr_hash);
    fprintf(log, "data              <%p> = %p\n", &cur_stack->data, cur_stack->data);
    fprintf(log, "hash              <%p> = %d\n", &cur_stack->hash, cur_stack->hash);
    fprintf(log, "right canary      <%p> = %lf - ", &cur_stack->right_cnry, cur_stack->right_cnry);
    if (cur_stack->right_cnry == DFLT_STACK_CNRY_VAL)
        fprintf(log, "ALIVE\n");
    else
        fprintf(log, "DEAD!\n");
    fprintf(log, "==================================================================\n\n");
    
    if (is_valid_data) {
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

            if (pos == 0 || pos == cur_stack->cpcty + 1) {
                if (cur_stack->data[pos] != DFLT_STACK_CNRY_VAL) 
                    fprintf(log, " - DEAD!");
                else
                    fprintf(log, " - ALIVE");
            }
            fprintf(log, "\n");
            if(pos == 0)
                fprintf(log, "\n");
        } 
        fprintf(log, "##########==============================================##########\n\n");
    } else

    fprintf(log, "invalid data pointer, unable to output array.\n");

    fclose(log);
}

int m_stack_verifier(m_stack *cur_stack, char *file_name, int line_num)
{
    FILE *log = fopen("stack_log.txt", "a");
    
    if (cur_stack == NULL) {
        LOG_PRINT(STACK_NULL)
        fprintf(log, "%d: pointer to m_stack is NULL.\n", STACK_NULL);

        fclose(log);

        return STACK_NULL;
    }

    if (cur_stack->data == NULL) {
        LOG_PRINT(STACK_DATA_NULL)
        fprintf(log, "%d: pointer to m_stack->data is NULL.\n", STACK_DATA_NULL);

        fclose(log);
        m_stack_dump(cur_stack, INVALID_DATA);

        return STACK_DATA_NULL;
    }

    if (cur_stack->left_cnry != DFLT_STACK_CNRY_VAL) {
        LOG_PRINT(STACK_LEFT_CANARY_DIED)
        fprintf(log, "%d: left canary died.\n", STACK_LEFT_CANARY_DIED);
        
        fclose(log);
        m_stack_dump(cur_stack, VALID_DATA);
        
        return STACK_LEFT_CANARY_DIED;
    }

    if (cur_stack->right_cnry != DFLT_STACK_CNRY_VAL) {
        LOG_PRINT(STACK_RIGHT_CANARY_DIED)
        fprintf(log, "%d: right canary died.\n", STACK_RIGHT_CANARY_DIED);

        fclose(log);
        m_stack_dump(cur_stack, VALID_DATA);

        return STACK_RIGHT_CANARY_DIED;
    }

    int old_data_ptr_hash = cur_stack->data_ptr_hash;
    count_data_ptr_hash(cur_stack);

    if (old_data_ptr_hash != cur_stack->data_ptr_hash) {
        LOG_PRINT(STACK_WRONG_DATA_PTR);
        fprintf(log, "%d: wrong data ptr.\n", STACK_WRONG_DATA_PTR);

        fclose(log);
        m_stack_dump(cur_stack, INVALID_DATA);

        return STACK_WRONG_DATA_PTR;
    }

    if(cur_stack->size > MAX_STACK_SIZE_VAL || cur_stack->size > cur_stack->cpcty || cur_stack->size < 0) {
        LOG_PRINT(STACK_OVERFLOW)
        fprintf(log, "%d: m_stack overflow.\n", STACK_OVERFLOW);

        fclose(log);
        m_stack_dump(cur_stack, INVALID_DATA);

        return STACK_OVERFLOW;
    }

    if (cur_stack->data[0] != DFLT_STACK_CNRY_VAL) {
        LOG_PRINT(STACK_LEFT_DATA_CANARY_DIED)
        fprintf(log, "%d: left data canary died.\n", STACK_LEFT_DATA_CANARY_DIED);

        fclose(log);
        m_stack_dump(cur_stack, VALID_DATA);

        return STACK_LEFT_DATA_CANARY_DIED;
    }

    if (cur_stack->data[cur_stack->cpcty + 1] != DFLT_STACK_CNRY_VAL) {
        LOG_PRINT(STACK_RIGHT_DATA_CANARY_DIED)
        fprintf(log, "%d: right data canary died.\n", STACK_RIGHT_DATA_CANARY_DIED);

        fclose(log);
        m_stack_dump(cur_stack, VALID_DATA);

        return STACK_RIGHT_DATA_CANARY_DIED;
    }

    int old_hash = cur_stack->hash;
    count_hash(cur_stack);

    if (old_hash!= cur_stack->hash) {
        LOG_PRINT(STACK_WRONG_HASH)
        fprintf(log, "%d: hash is wrong, data corrupted.\n", STACK_WRONG_HASH);

        fclose(log);
        m_stack_dump(cur_stack, VALID_DATA);

        return STACK_WRONG_HASH;
    }

    m_stack_type *first = cur_stack->data + cur_stack->size + 1;
    m_stack_type *last  = cur_stack->data + cur_stack->cpcty + 1;
    for (m_stack_type *ptr = first; ptr != last; ptr++) {
        if (!isnan(*ptr)) {
            LOG_PRINT(STACK_POISON_SPILLED);
            fprintf(log, "%d: poison got spilled.\n", STACK_POISON_SPILLED);

            fclose(log);
            m_stack_dump(cur_stack, VALID_DATA);

            return STACK_POISON_SPILLED;
        }
    }

    fclose(log);

    return STACK_ALRIGHT;
}