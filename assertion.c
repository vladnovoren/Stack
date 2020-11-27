#include "assertion.h"
#include "funcs_prv.h"
#include "locale.h"

char *error_info(int err_code)
{
    switch (err_code) {
        case STACK_ALRIGHT:
            return "stack is alright";

        case STACK_NULL:
            return "stack pointer is NULL";

        case STACK_DATA_NULL:
            return "stack data pointer is NULL";

        case STACK_LEFT_CANARY_DIED:
            return "left canary died";
        
        case STACK_RIGHT_CANARY_DIED:
            return "right canary died";
        
        case STACK_OVERFLOW:
            return "stack overflow";

        case STACK_WRONG_DATA_PTR_HASH:
            return "invalid pointer to stack data or hash of data pointer";
        
        case STACK_LEFT_DATA_CANARY_DIED:
            return "left canary of data died";
        
        case STACK_RIGHT_DATA_CANARY_DIED:
            return "right canary of data died";
        
        case STACK_WRONG_DATA_HASH:
            return "hash of data contain is wrong";
        
        case STACK_POISON_SPILLED:
            return "stack data poison spilled";
        default:
            return "something went wrong";
    }
}

void log_print(FILE *log, int err_code, char *file_name, const char *func_name, size_t line)
{
    assert(log != NULL);
    assert(file_name != NULL);
    assert(func_name != NULL);

    fprintf(log, "file: %s, function: %s, line: %zu\n", file_name, func_name, line);
    fprintf(log, "verifier returned error code %d: ", err_code);
    fprintf(log, "%s.\n", error_info(err_code));
}

void m_stack_dump(m_stack *cur_stack, int is_data_valid)
{
    assert(cur_stack != NULL);
    
    FILE *log = fopen("stack_log.txt", "a");

    fprintf(log, "\n\n##########========================== m_stack dump ==========================##########\n\n");
    fprintf(log, "the angle quotes contain the address of the variable.\n\n");
    fprintf(log, "main m_stack characteristics:\n");
    fprintf(log, "======================================================================================\n");
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
    fprintf(log, "hash              <%p> = %d\n", &cur_stack->data_hash, cur_stack->data_hash);
    fprintf(log, "right canary      <%p> = %lf - ", &cur_stack->right_cnry, cur_stack->right_cnry);
    if (cur_stack->right_cnry == DFLT_STACK_CNRY_VAL)
        fprintf(log, "ALIVE\n");
    else
        fprintf(log, "DEAD!\n");
    fprintf(log, "======================================================================================\n\n");
    
    if (is_data_valid == VALID_DATA) {
        fprintf(log, "\noutput of m_stack data array:\n");
        fprintf(log, "======================================================================================\n");

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
        fprintf(log, "##########==================================================================##########\n\n");
    } else
    fprintf(log, "invalid data pointer or size, unable to output array.\n");

    fprintf(log, "\n\n\n\n");

    fclose(log);
}

//file_name, func_name, line_num

void m_stack_verifier(m_stack *cur_stack, char *file_name, const char *func_name, int line_num, int errors[11])
{
    FILE *log = fopen("stack_log.txt", "a");
    int is_data_valid = VALID_DATA;
    int is_stack_pointer_valid = VALID_DATA;

    if (cur_stack == NULL) {
        log_print(log, STACK_NULL, file_name, func_name, line_num);

        is_stack_pointer_valid = INVALID_DATA;
        errors[STACK_NULL] = INVALID_DATA;
        errors[STACK_ALRIGHT] = INVALID_DATA;
        return;
    }

    if (cur_stack->data == NULL) {
        log_print(log, STACK_DATA_NULL, file_name, func_name, line_num);

        is_data_valid = INVALID_DATA;
        errors[STACK_DATA_NULL] = INVALID_DATA;
        errors[STACK_ALRIGHT] = INVALID_DATA;
    }

    if (cur_stack->left_cnry != DFLT_STACK_CNRY_VAL) {
        log_print(log, STACK_LEFT_CANARY_DIED, file_name, func_name, line_num);
        
        errors[STACK_LEFT_CANARY_DIED] = INVALID_DATA;
        errors[STACK_ALRIGHT] = INVALID_DATA;
    }

    if (cur_stack->right_cnry != DFLT_STACK_CNRY_VAL) {
        log_print(log, STACK_RIGHT_CANARY_DIED, file_name, func_name, line_num);

        errors[STACK_RIGHT_CANARY_DIED] = INVALID_DATA;
        errors[STACK_ALRIGHT] = INVALID_DATA;
    }

    if(cur_stack->size > MAX_STACK_SIZE_VAL || cur_stack->size > cur_stack->cpcty || cur_stack->size < 0) {
        log_print(log, STACK_OVERFLOW, file_name, func_name, line_num);

        is_data_valid = INVALID_DATA;
        errors[STACK_OVERFLOW] = INVALID_DATA;
        errors[STACK_ALRIGHT] = INVALID_DATA;
    }

    int old_data_ptr_hash = cur_stack->data_ptr_hash;
    count_data_ptr_hash(cur_stack);

    if (old_data_ptr_hash != cur_stack->data_ptr_hash) {
        log_print(log, STACK_WRONG_DATA_PTR_HASH, file_name, func_name, line_num);
        
        is_data_valid = INVALID_DATA;
        errors[STACK_WRONG_DATA_PTR_HASH] = INVALID_DATA;
        errors[STACK_ALRIGHT] = INVALID_DATA;
    }

    if (is_data_valid == VALID_DATA)
    {
        if (cur_stack->data[0] != DFLT_STACK_CNRY_VAL) {
            log_print(log, STACK_LEFT_DATA_CANARY_DIED, file_name, func_name, line_num);

            is_data_valid = INVALID_DATA;
            errors[STACK_LEFT_DATA_CANARY_DIED] = INVALID_DATA;
            errors[STACK_ALRIGHT] = INVALID_DATA;
        }

        if (cur_stack->data[cur_stack->cpcty + 1] != DFLT_STACK_CNRY_VAL) {
            log_print(log, STACK_RIGHT_DATA_CANARY_DIED, file_name, func_name, line_num);

            is_data_valid = INVALID_DATA;
            errors[STACK_RIGHT_DATA_CANARY_DIED] = INVALID_DATA;
            errors[STACK_ALRIGHT] = INVALID_DATA;
        }

        int old_hash = cur_stack->data_hash;
        count_data_hash(cur_stack);

        if (old_hash!= cur_stack->data_hash) {
            log_print(log, STACK_WRONG_DATA_HASH, file_name, func_name, line_num);

            is_data_valid = INVALID_DATA;
            errors[STACK_WRONG_DATA_HASH] = INVALID_DATA;
            errors[STACK_ALRIGHT] = INVALID_DATA;
        }

        m_stack_type *first = cur_stack->data + cur_stack->size + 1;
        m_stack_type *last  = cur_stack->data + cur_stack->cpcty + 1;

        for (m_stack_type *ptr = first; ptr != last; ptr++) {
            if (!isnan(*ptr)) {
                log_print(log, STACK_POISON_SPILLED, file_name, func_name, line_num);

                is_data_valid = INVALID_DATA;
                errors[STACK_POISON_SPILLED] = INVALID_DATA;
                errors[STACK_ALRIGHT] = INVALID_DATA;
            }
        }
    } else {
        for (size_t err_code = STACK_LEFT_DATA_CANARY_DIED; err_code <= STACK_POISON_SPILLED; err_code++)
            errors[err_code] = UNDEF_STATE;
    }

    if (errors[STACK_ALRIGHT] != VALID_DATA)
    {
        printf("\nfile: %s, function: %s, line: %d\n", file_name, func_name, line_num);
        printf("stack is broken.\n");
        printf("you can see more info in \"stack_log.txt\".\n");
    }


    if (is_stack_pointer_valid == INVALID_DATA) {
        fprintf(log , "unable to show stack dump because pointer to stack is NULL.\n");
        fclose(log);
    } else if (errors[STACK_ALRIGHT] != VALID_DATA) {
        fclose(log);
        m_stack_dump(cur_stack, is_data_valid);
    }
    return;
}