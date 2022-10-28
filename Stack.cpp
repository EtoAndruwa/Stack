#include <stdio.h>
#include <stdlib.h>

typedef struct
    {
        int * data;
        int size = 1;

    }Stack;

void StackInit(Stack * st);
void StackPush(Stack * st, int push_value);
int StackCheck(Stack * st);

enum Error_list
    {
            ERR_NULL_DATA = 1,
            ERR_OUT_OF_STACK = 2
    };

int stack_size = 0;
int error_code = 0;

int main()
    {
        Stack a;
        int push_value = 0;

        StackInit(&a);

        scanf("%d", &push_value);
        StackPush(&a, push_value);

        scanf("%d", &push_value);
        StackPush(&a, push_value);

        scanf("%d", &push_value);
        StackPush(&a, push_value);



        free(a.data);
        return 0;
    }

void StackInit(Stack * st)
    {
        stack_size = 5;
        st->size = 0;
        st->data = (int *)calloc(stack_size, sizeof(int));
        StackCheck(st);
    }
//
void StackPush(Stack * st, int push_value)
    {
        StackCheck(st);
        st->data[st->size++] = push_value;
        StackCheck(st);
    }

//int StackPop(Stack * st)
//    {
//        st->data[st->size++] = push_value;
//
//    }

int StackCheck(Stack * st)
    {
        if(st->data == NULL)
            {
                return ERR_NULL_DATA;
            }
        else if(st->size >= 5)
            {
                return ERR_OUT_OF_STACK;
            }
    }
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
        printf("Stack info\n");
        printf("Stack size = %d\n\n", a.size);

        for(int i = 0; i < stack_size; i++)
            {
                printf("data[%d] = %d\n", i, a.data[i]);
            }
    }



