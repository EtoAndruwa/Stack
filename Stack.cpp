#include  "stack.h"

#define FUNC_NAME __func__ // used in order to get name of the function which called the error
#define FUNC_LINE __LINE__ // used in order to get the line from which the error was called

void StackCtor(Stack * st) // OK
{   
    printf("Enter stack capacity: ");
    scanf("%ld", &st->capacity);

    st->stack_pointer = calloc(1, 2 * sizeof(size_t) + st->capacity * sizeof(stack_type)); // FREE?

    st->left_canary_position = (size_t*)st->stack_pointer;
    st->data = (stack_type*)(st->left_canary_position + 1);
    st->right_canary_position = (size_t*)(st->data + st->capacity);

    st->left_canary_position[0] = CANARY;
    st->right_canary_position[0] = CANARY;

    st->hash = 0;   

    printf("LEFT CANARY ADDRESS: %p\n", st->left_canary_position);
    printf("DATA ADDRESS: %p\n", st->data);
    printf("RIGHT CANARY ADDRESS: %p\n", st->right_canary_position);

    StackCheck(st, FUNC_NAME, FUNC_LINE);

    for(size_t i = 0; i < st->capacity ; i++)
    {
        st->data[i] = POISON_VALUE;
    }

    StackCheck(st, FUNC_NAME, FUNC_LINE);
}
    
void StackPush(Stack * st, stack_type push_value) // OK
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    st->data[st->next_empty_cell++] = push_value; 

    st->hash = st->hash + push_value; // calculating new hash value
    // printf("Hash value: %ld", st->hash);

    StackCheck(st, FUNC_NAME, FUNC_LINE);
}

void StackPop(Stack * st) // OK
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    stack_type poped_value = st->data[st->next_empty_cell - 1];
    st->data[st->next_empty_cell - 1] = POISON_VALUE;
    st->next_empty_cell--;

    st->hash = st->hash - poped_value; // calculating new hash value
    // printf("Hash value: %ld", st->hash);

    StackCheck(st, FUNC_NAME, FUNC_LINE);
}

void StackDump(Stack * st, const char * FUNCT_NAME, int FUNCT_LINE)
{
    FILE *file = fopen("LOG.txt", "a+");
    if (file == NULL)
    {
        printf("ERROR: LOG file cannot be open");
    }
    else
    {   
        fprintf(file, "-------------------START OF STACK DUMP------------------------\n\n");
        fprintf(file, "Left canary address = %p\n", st->left_canary_position);
        fprintf(file, "Data address = %p\n", st->data);
        fprintf(file, "Right canary address = %p\n", st->right_canary_position);
        fprintf(file, "Stack capacity = %ld\n", st->capacity);
        fprintf(file, "Stack next_empty_cell = %ld\n\n", st->next_empty_cell);
        fprintf(file, "Stack hash = %ld\n\n", st->hash);

        fprintf(file, "Stack error code = %ld (%s)\n", st->error_code, Enum_to_string(st->error_code)); // check
        fprintf(file, "Called from file: %s\n", __FILE__);
        fprintf(file, "Called error function name: %s\n", FUNCT_NAME);
        fprintf(file, "Called from line: %d\n", FUNCT_LINE);    
        fprintf(file, "Date when was called: %s\n", __DATE__);
        fprintf(file, "Time when was called: %s\n\n", __TIME__);

        fprintf(file, "LEFT CANARY = %ld\n", st->left_canary_position[0]);
        for(int i = 0; i < st->capacity; i++)
        {
                fprintf(file, "data[%d] = %.3lf", i, st->data[i]);
                fprintf(file, "\t address %p\n", st->data + i);
        }
        fprintf(file, "RIGHT CANARY = %ld\n", st->right_canary_position[0]);
        fprintf(file, "--------------------END OF STACK DUMP--------------------------\n\n");
    }
    fclose(file);
}

void StackMul(Stack * st) // OK
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    st->data[st->next_empty_cell - 2] = st->data[st->next_empty_cell - 1] * st->data[st->next_empty_cell - 2];
    st->data[st->next_empty_cell - 1] = POISON_VALUE;
    st->next_empty_cell--;

    Calculate_hash(st);

    StackCheck(st, FUNC_NAME, FUNC_LINE);
}

void StackSub(Stack * st) // OK
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    st->data[st->next_empty_cell - 2] = st->data[st->next_empty_cell - 2] - st->data[st->next_empty_cell - 1];
    st->data[st->next_empty_cell - 1] = POISON_VALUE;
    st->next_empty_cell--;

    Calculate_hash(st);

    StackCheck(st, FUNC_NAME, FUNC_LINE);
}

void StackDiv(Stack * st) // OK
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    st->data[st->next_empty_cell - 2] = (st->data[st->next_empty_cell - 2]) / (st->data[st->next_empty_cell - 1]);
    st->data[st->next_empty_cell - 1] = POISON_VALUE;
    st->next_empty_cell--;

    Calculate_hash(st);

    StackCheck(st, FUNC_NAME, FUNC_LINE);
}

void StackPrint(Stack * st) // OK
{   
    printf("\n");
    printf("LEFT_CANARY: = %ld\n", *(st->left_canary_position));
    for(size_t i = 0; i < st->capacity; i++) // check
    {
        printf("data[%ld] = %.3lf\n", i, st->data[i]);
    }
    printf("RIGHT_CANARY: = %ld\n\n", *(st->right_canary_position));
}

void StackAdd(Stack * st) // OK
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE);

    st->data[st->next_empty_cell - 2] = (st->data[st->next_empty_cell - 2]) + (st->data[st->next_empty_cell - 1]);
    st->data[st->next_empty_cell - 1] = POISON_VALUE;
    st->next_empty_cell--;

    Calculate_hash(st);

    StackCheck(st, FUNC_NAME, FUNC_LINE);
}

void StackLogic(Stack * st, char * command, stack_type push_value) // OK
{
    if(strcmp(command, "PUSH") == 0)
    {   
        StackRealocUp(st);
        StackPush(st, push_value);
    }
    else if(strcmp(command, "POP") == 0)
    {   
        StackRealocDown(st);
        StackPop(st);
    }
    else if(strcmp(command, "ADD") == 0)
    {   
        StackRealocDown(st);
        StackAdd(st);
    }
    else if(strcmp(command, "SUB") == 0)
    {   
        StackRealocDown(st);
        StackSub(st);
    }
    else if(strcmp(command, "MUL") == 0)
    {   
        StackRealocDown(st);
        StackMul(st);
    }
    else if(strcmp(command, "DIV") == 0)
    {   
        StackRealocDown(st);
        StackDiv(st);
    }
}

void StackConsoleWork(Stack * st) // OK
{
    char * command = (char *)calloc(MAX_LINE_COMMAND, sizeof(size_t));
    stack_type push_value = 0;
    do
    {
        scanf("%s", command);
        if(strcmp(command, "PUSH") == 0)
        {
            scanf(" %lf", &push_value);
        }

        StackLogic(st, command, push_value);
        StackPrint(st);

    }
    while(strcmp(command, "HLT") != 0)    ;
    free(command);
}

void StackCheck(Stack * st, const char * FUNCT_NAME, int FUNCT_LINE)
{   
    if(st->data == nullptr)
    {
        st->error_code = ERR_NULL_DATA;
        StackDump(st, FUNCT_NAME, FUNCT_LINE);
        StackDtor(st);
        abort();
    }
    else if(st->next_empty_cell > st->capacity)
    {
        st->error_code = ERR_OUT_OF_STACK_RIGHT;
        StackDump(st, FUNCT_NAME, FUNCT_LINE);
        StackDtor(st);
        abort();
    }
    else if(st->next_empty_cell < 0)
    {   
        st->error_code = ERR_OUT_OF_STACK_LEFT;
        StackDump(st, FUNCT_NAME, FUNCT_LINE);
        StackDtor(st);
        abort();
    }
    else if(st->left_canary_position[0] != CANARY)
    {   
        st->error_code = ERR_LEFT_CANARY_DEAD;
        StackDump(st, FUNCT_NAME, FUNCT_LINE);
        StackDtor(st);
        abort();
    }
    else if(st->right_canary_position[0] != CANARY)
    {   
        st->error_code = ERR_RIGHT_CANARY_DEAD;
        StackDump(st, FUNCT_NAME, FUNCT_LINE);
        StackDtor(st);
        abort();
    }
    else if(st->hash != Get_cur_value_of_hash(st))   
    {
        st->error_code = ERR_HASH_CHANGED;
        StackDump(st, FUNCT_NAME, FUNCT_LINE);
        StackDtor(st);
        abort();
    }   
}

void StackDtor(Stack * st)
{
    for(int  i = 0; i < st->capacity; i++)
    {
        st->data[i] = POISON_VALUE;
    }
    st->capacity = 0;
    st->next_empty_cell = 0;
    st->hash = 0;
    st->left_canary_position[0] = 0;
    st->right_canary_position[0] = 0;

    st->left_canary_position = nullptr;
    st->right_canary_position = nullptr;
    st->data = nullptr;

    free(st->stack_pointer);
    st->stack_pointer = nullptr;
}

void StackRealocUp(Stack* st) // OK
{
    if(st->next_empty_cell == st->capacity)
    {   
        st->capacity *= 2;

        st->stack_pointer = realloc(st->stack_pointer, st->capacity * sizeof(stack_type) + 2 * sizeof(size_t)); //FREE?

        st->left_canary_position = (size_t*)st->stack_pointer;
        st->data = (stack_type*)(st->left_canary_position + 1);
        st->right_canary_position = (size_t*)(st->data + st->capacity);

        for(size_t i = st->next_empty_cell; i < st->capacity ; i++)
        {
            st->data[i] = POISON_VALUE;
        }

        st->left_canary_position[0] = CANARY;
        st->right_canary_position[0] = CANARY;

        StackCheck(st, FUNC_NAME, FUNC_LINE);
    }
}

void StackRealocDown(Stack* st) // OK
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    if((st->next_empty_cell <= (st->capacity - 2) / 2) && (st->capacity > 3))
    {   
        st->capacity = st->capacity - ((st->capacity -1 )/2);

        st->stack_pointer = realloc(st->stack_pointer, st->capacity * sizeof(stack_type) + 2 * sizeof(size_t));

        st->left_canary_position = (size_t*)st->stack_pointer;
        st->data = (stack_type*)(st->left_canary_position + 1);
        st->right_canary_position = (size_t*)(st->data + st->capacity);

        for(size_t i = st->next_empty_cell; i < st->capacity ; i++)
        {
            st->data[i] = POISON_VALUE;
        }

        st->left_canary_position[0] = CANARY;
        st->right_canary_position[0] = CANARY;

        StackCheck(st, FUNC_NAME, FUNC_LINE);
    }
}

void Calculate_hash(Stack * st) // OK
{
    st->hash = 0; // calculating new hash
    for(size_t i = 0; i < st->next_empty_cell; i++)
    {
        st->hash = st->hash + st->data[i]; 
    }
    printf("Hash value: %ld", st->hash);
}

size_t Get_cur_value_of_hash(Stack * st) // OK
{   
    size_t cur_value_of_hash = 0;

    for(size_t i = 0; i < st->next_empty_cell; i++) // CHECK
    {
        cur_value_of_hash = cur_value_of_hash + st->data[i]; 
    }    

    return cur_value_of_hash;
}

const char* Enum_to_string(size_t code) // CHECK
{
    switch(code)
    {
        case 1:
            return "ERR_NULL_DATA";
            break;
        case 2:
            return "ERR_OUT_OF_STACK_RIGHT";
            break;
        case 3:
            return "ERR_OUT_OF_STACK_LEFT";
            break;
        case 4:
            return "ERR_LEFT_CANARY_DEAD";
            break;
        case 5:
            return "ERR_RIGHT_CANARY_DEAD";
            break;
        case 6:
            return "ERR_HASH_CHANGED";
            break;
        default:
            return "OK"; // CHECK
            break;
    }
}






