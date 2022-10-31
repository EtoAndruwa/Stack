#include  "stack.h"

void StackInit(Stack * st, size_t capacity)
{
    st->capacity = capacity;
    st->size = 0;
    st->data = (stack_type *)calloc(capacity, sizeof(stack_type));
//  StackCheck(st);
}

void StackPush(Stack * st, stack_type push_value)
{
//  StackCheck(st);
    st->data[st->size++] = push_value;
//  StackCheck(st);
}

stack_type StackPop(Stack * st)
{
    stack_type temp = st->data[st->size - 1];
    st->data[st->size - 1] = 0;
    st->size--;
    return temp;

}


void StackDump(Stack * st)
{
    FILE *file = fopen("log.txt", "rb");
    if (file == NULL)
    {
        printf("ERROR: log file cannot be open");
    }
    else
    {
        fprintf(file, "\nStack info\n");
        fprintf(file, "Stack size = %ld\n\n", st->capacity);

        for(int i = 0; i < st->capacity; i++)
        {
            if(i == st->capacity - 1)
            {
                fprintf(file, "data[%d] = %.3lf\n\n", i, st->data[i]);
            }
            else
            {
                fprintf(file, "data[%d] = %.3lf\n", i, st->data[i]);
            }
        }
        fprintf(file, "----------------------------------------------");
    }
    fclose(file);
}

void StackMul(Stack * st)
{
    st->data[st->size - 2] = st->data[st->size - 1] * st->data[st->size - 2];
    st->data[st->size - 1] = 0;
    st->size--;
}

void StackSub(Stack * st)
{
    st->data[st->size - 2] = st->data[st->size - 2] - st->data[st->size - 1];
    st->data[st->size - 1] = 0;
    st->size--;
}

void StackDiv(Stack * st)
{
    st->data[st->size - 2] = (st->data[st->size - 2]) / (st->data[st->size - 1]);
    st->data[st->size - 1] = 0;
    st->size--;
}

void StackPrint(Stack * st)
{
    for(int i = 0; i < st->capacity; i++)
    {
        if(i == st->capacity-1)
        {
            printf("data[%d] = %.3lf\n\n", i, st->data[i]);
        }
        else
        {
            printf("data[%d] = %.3lf\n", i, st->data[i]);
        }
    }
}

void StackAdd(Stack * st)//OK
{
    st->data[st->size - 2] = (st->data[st->size - 2]) + (st->data[st->size - 1]);
    st->data[st->size - 1] = 0;
    st->size--;
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


//int StackCheck(Stack * st)
//{
//        if(st->data == NULL)
//            {
//                return ERR_NULL_DATA;
//            }
//        else if(st->size >= 5)
//            {
//                return ERR_OUT_OF_STACK;
//            }
//    }
//
//void StackDetor(Stack * st)
//    {
//        free(st->data);
//    }

//void StackRealoc(Stack * a)
//    {
//        free(a->data);
//
//    }





