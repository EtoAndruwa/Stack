#include  "stack.h"

void StackCtor(Stack * st)
{   
    printf("Enter stack capacity: ");
    scanf("%ld", &st->capacity);
    st->capacity = st->capacity + 2; 
    st->size = 1;
    st->data = (stack_type *)calloc(st->capacity, sizeof(stack_type));
    // StackCheck(st);
    for(int  i = 0; i < st->capacity; i++)
    {   
        if((i == 0) || (i == (st->capacity - 1)))
        {
            st->data[i] = CANARY;
        }
        else
        {
            st->data[i] = POISON_VALUE;
        }
    }

    *(st->data + st->capacity) = CANARY;
    *((st->data) - 1 * sizeof(stack_type)) = CANARY;
    StackCheck(st);
}

void StackPush(Stack * st, stack_type push_value)
{
    StackCheck(st);
    st->data[st->size++] = push_value; 
    StackCheck(st);
}

stack_type StackPop(Stack * st)
{   
    StackCheck(st);
    stack_type temp = st->data[st->size - 1];
    st->data[st->size - 1] = POISON_VALUE;
    st->size--;
    StackCheck(st);
    return temp;
}

void StackDump(Stack * st)
{
    FILE *file = fopen("log.txt", "a+");
    if (file == NULL)
    {
        printf("ERROR: log file cannot be open");
    }
    else
    {
        fprintf(file, "-------------------START OF STACK DUMP------------------------\n\n");
        fprintf(file, "Stack * data = %p\n", st->data);
        fprintf(file, "Stack capacity = %ld\n", st->capacity);
        fprintf(file, "Stack size = %ld\n", st->size);
        fprintf(file, "Stack error_code = %ld\n", st->error_code);

        fprintf(file, "data[-1] = %.3lf", *((st->data) - 1 * sizeof(stack_type)));
        fprintf(file, "\t address %p\n", ((st->data) - 1));
        for(int i = 0; i < st->capacity; i++)
        {
            if(i == st->capacity - 1)
            {
                fprintf(file, "data[%d] = %.3lf", i, st->data[i]);
                fprintf(file, "\t address %p\n", st->data + i);
            }   
            else
            {
                fprintf(file, "data[%d] = %.3lf", i, st->data[i]);
                fprintf(file, "\t address %p\n", st->data + i);
            }
        }
        fprintf(file, "data[+1] = %.3lf", *(st->data + st->capacity));
        fprintf(file, "\t address %p\n\n", st->data + st->capacity);
        fprintf(file, "--------------------END OF STACK DUMP--------------------------\n\n");
    }
    fclose(file);
}

void StackMul(Stack * st)
{   
    StackCheck(st);
    st->data[st->size - 2] = st->data[st->size - 1] * st->data[st->size - 2];
    st->data[st->size - 1] = POISON_VALUE;
    st->size--;
    StackCheck(st);
}

void StackSub(Stack * st)
{   
    StackCheck(st);
    st->data[st->size - 2] = st->data[st->size - 2] - st->data[st->size - 1];
    st->data[st->size - 1] = POISON_VALUE;
    st->size--;
    StackCheck(st);
}

void StackDiv(Stack * st)
{   
    StackCheck(st);
    st->data[st->size - 2] = (st->data[st->size - 2]) / (st->data[st->size - 1]);
    st->data[st->size - 1] = POISON_VALUE;
    st->size--;
    StackCheck(st);
}

void StackPrint(Stack * st)
{   
    printf("data[-1] = %.3lf", *((st->data) - 1 * sizeof(stack_type)));
    printf("\t address %p\n", ((st->data) - 1));
    for(int i = 0; i < st->capacity; i++)
    {
        if(i == st->capacity - 1)
        {
            printf("data[%d] = %.3lf", i, st->data[i]);
            printf("\t address %p\n", st->data + i);
        }
        else
        {
            printf("data[%d] = %.3lf", i, st->data[i]);
            printf("\t address %p\n", st->data + i);
        }
    }
    printf("data[+1] = %.3lf", *(st->data + st->capacity));
    printf("\t address %p\n\n", st->data + st->capacity);
}

void StackAdd(Stack * st)//OK
{   
    StackCheck(st);
    st->data[st->size - 2] = (st->data[st->size - 2]) + (st->data[st->size - 1]);
    st->data[st->size - 1] = POISON_VALUE;
    st->size--;
    StackCheck(st);
}

void StackLogic(Stack * st, char * command, stack_type push_value)//OK
{
    if(strcmp(command, "PUSH") == 0)
    {
        StackPush(st, push_value);
    }
    else if(strcmp(command, "POP") == 0)
    {
        StackPop(st);
    }
    else if(strcmp(command, "ADD") == 0)
    {
        StackAdd(st);
    }
    else if(strcmp(command, "SUB") == 0)
    {
        StackSub(st);
    }
    else if(strcmp(command, "MUL") == 0)
    {
        StackMul(st);
    }
    else if(strcmp(command, "DIV") == 0)
    {
        StackDiv(st);
    }
}

void StackConsoleWork(Stack * st)
{
    char * command = (char *)calloc(MAX_LINE_COMMAND, sizeof(size_t));
    stack_type push_value = 0;
    do{
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

void StackCheck(Stack * st)
{   
    if(st->data == nullptr)
    {
        st->error_code = ERR_NULL_DATA;
        StackDump(st);
        StackDtor(st);
        abort();
    }
    else if(st->size > st->capacity)
    {
        st->error_code = ERR_OUT_OF_STACK_RIGHT;
        StackDump(st);
        StackDtor(st);
        abort();
    }
    else if(st->size < 0)
    {   
        st->error_code = ERR_OUT_OF_STACK_LEFT;
        StackDump(st);
        StackDtor(st);;
        abort();
    }
    else if(*((st->data) - 1 * sizeof(stack_type)) != CANARY)
    {   
        st->error_code = ERR_LEFT_BUFFER_CANARY_DEAD;
        StackDump(st);
        StackDtor(st);
        abort();
    }
    else if(*(st->data + st->capacity) != CANARY)
    {   
        st->error_code = ERR_RIGHT_BUFFER_CANARY_DEAD;
        StackDump(st);
        StackDtor(st);
        abort();
    }
    else if(st->data[0] != CANARY)
    {   
        st->error_code = ERR_LEFT_CANARY_DEAD;
        StackDump(st);
        StackDtor(st);
        StackPrint(st);
        abort();
    }
    else if(st->data[st->capacity-1] != CANARY)
    {   
        st->error_code = ERR_RIGHT_CANARY_DEAD;
        StackDump(st);
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
    StackPrint(st);
    st->capacity = POISON_VALUE;
    st->size = POISON_VALUE;
    st->data = nullptr;
    free(st->data);
   }

//void StackRealoc(Stack * a)
//    {
//        free(a->data);
//
//    }





