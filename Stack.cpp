#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double stack_type;

typedef struct
    {
        stack_type * data;
        int size = 0;

    }Stack;

void StackInit(Stack * st);
void StackPush(Stack * st, stack_type push_value);
//int StackCheck(Stack * st);
void StackDamp(Stack * st);
stack_type StackPop(Stack * st);
void StackMul(Stack * st);
void StackSub(Stack * st);
void StackDiv(Stack * st);
void StackPrint(Stack * st);
void StackLogic(Stack * st, char command[], stack_type push_value);
void StackAdd(Stack * st);

enum error_list
    {
            ERR_NULL_DATA = 1,
            ERR_OUT_OF_STACK = 2
    };


int stack_size = 0;
int error_code = 0;

int main()
    {
        Stack a;
        stack_type push_value = 0;
        stack_type poped_value = 0;

        StackInit(&a);

        StackPrint(&a);

        char command[4] = "";

//        const char *ñommand[6];
//        command[0] = "PUSH";
//        command[1] = "POP";
//        command[2] = "ADD";
//        command[3] = "SUB";
//        command[4] = "MUL";
//        command[5] = "DIV";

        do{
            scanf("%s %lf", &command, &push_value);


            printf("Command: %s\n", command);
            printf("Value = %.3lf\n", push_value);

            StackLogic(&a, command, push_value);
            StackPrint(&a);
          }
        while(strcmp(command, "HLT") != 0);

//        scanf("%lf", &push_value);
//        StackPush(&a, push_value);
//        StackPrint(&a);
//
//        scanf("%lf", &push_value);
//        StackPush(&a, push_value);
//        StackPrint(&a);
//
//        StackAdd(&a);


//
//        scanf("%lf", &push_value);
//        StackPush(&a, push_value);
//        StackPrint(&a);
//
//        scanf("%lf", &push_value);
//        StackPush(&a, push_value);
//        StackPrint(&a);
//
//        scanf("%lf", &push_value);
//        StackPush(&a, push_value);
//        StackPrint(&a);

//        StackPrint(&a);
//        poped_value = StackPop(&a);
//        printf("Poped value = %.3lf\n", poped_value);
//        StackPrint(&a);
//
//        StackMul(&a);
//        StackPrint(&a);
//
//        StackSub(&a);
//        StackPrint(&a);
//
//        StackDiv(&a);
//        StackPrint(&a);
//        StackDamp(&a);
        free(a.data);
        return 0;
    }

void StackInit(Stack * st)
    {
        stack_size = 5;
        st->size = 0;
        st->data = (stack_type *)calloc(stack_size, sizeof(stack_type));
//        StackCheck(st);
    }

void StackPush(Stack * st, stack_type push_value)
    {
//        StackCheck(st);
        st->data[st->size++] = push_value;
//        StackCheck(st);
    }

stack_type StackPop(Stack * st)
    {
        stack_type temp = st->data[st->size - 1];
        st->data[st->size - 1] = 0;
        st->size--;
        return temp;

    }

//int StackCheck(Stack * st)
//    {
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

void StackDamp(Stack * st)
    {

        FILE *f;
        f = fopen("log.txt", "a+"); // a+ (create + append) option will allow appending which is useful in a log file
        if (f == NULL)
            {
                printf("ERROR: log file cannot be open");
            }
        else
            {
                fprintf(f, "\nStack info\n");
                fprintf(f, "Stack size = %d\n\n", st->size);

                for(int i = 0; i < stack_size; i++)
                {
                    if(i == stack_size-1)
                        {
                            fprintf(f, "data[%d] = %.3lf\n\n", i, st->data[i]);
                        }
                    else
                        {
                            fprintf(f, "data[%d] = %.3lf\n", i, st->data[i]);
                        }
                }
            }
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
        for(int i = 0; i < stack_size; i++)
            {
                if(i == stack_size-1)
                    {
                        printf("data[%d] = %.3lf\n\n", i, st->data[i]);
                    }
                else
                    {
                        printf("data[%d] = %.3lf\n", i, st->data[i]);
                    }
            }
    }

void StackAdd(Stack * st)
    {
        st->data[st->size - 2] = (st->data[st->size - 2]) + (st->data[st->size - 1]);
        st->data[st->size - 1] = 0;
        st->size--;
    }

void StackLogic(Stack * st, char command[], stack_type push_value)
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




