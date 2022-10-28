#include <stdio.h>
#include <stdlib.h>

typedef struct
    {
        int * data;
        int size = 1;

    }Stack;

void StackInit(Stack * st);
void StackPush(Stack * st, int push_value);
//int StackCheck(Stack * st);
void StackDamp(Stack * st);
int StackPop(Stack * st);
void StackMul(Stack * st);
void StackSub(Stack * st);

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
        int poped_value = 0;

        StackInit(&a);

        scanf("%d", &push_value);
        StackPush(&a, push_value);
        StackDamp(&a);

        scanf("%d", &push_value);
        StackPush(&a, push_value);
        StackDamp(&a);

        scanf("%d", &push_value);
        StackPush(&a, push_value);
        StackDamp(&a);

        scanf("%d", &push_value);
        StackPush(&a, push_value);
        StackDamp(&a);

        scanf("%d", &push_value);
        StackPush(&a, push_value);
        StackDamp(&a);

        StackDamp(&a);
        poped_value = StackPop(&a);
        printf("Poped value = %d\n", poped_value);
        StackDamp(&a);

        StackMul(&a);
        StackDamp(&a);

        StackSub(&a);
        StackDamp(&a);



        free(a.data);
        return 0;
    }

void StackInit(Stack * st)
    {
        stack_size = 5;
        st->size = 0;
        st->data = (int *)calloc(stack_size, sizeof(int));
//        StackCheck(st);
    }

void StackPush(Stack * st, int push_value)
    {
//        StackCheck(st);
        st->data[st->size++] = push_value;
//        StackCheck(st);
    }

int StackPop(Stack * st)
    {
        int temp = st->data[st->size - 1];
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
        printf("\nStack info\n");
        printf("Stack size = %d\n\n", st->size);

        for(int i = 0; i < stack_size; i++)
            {
                if(i == stack_size-1)
                    {
                        printf("data[%d] = %d\n\n", i, st->data[i]);
                    }
                else
                    {
                        printf("data[%d] = %d\n", i, st->data[i]);
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



