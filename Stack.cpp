#include <stdio.h>
#include <stdlib.h>

typedef double stack_type;

typedef struct
    {
        stack_type * data;
        int size = 1;

    }Stack;

void StackInit(Stack * st);
void StackPush(Stack * st, stack_type push_value);
//int StackCheck(Stack * st);
void StackDamp(Stack * st);
stack_type StackPop(Stack * st);
void StackMul(Stack * st);
void StackSub(Stack * st);
void StackDiv(Stack * st);

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
        stack_type push_value = 0;
        stack_type poped_value = 0;

        StackInit(&a);

        scanf("%lf", &push_value);
        StackPush(&a, push_value);
        StackDamp(&a);

        scanf("%lf", &push_value);
        StackPush(&a, push_value);
        StackDamp(&a);

        scanf("%lf", &push_value);
        StackPush(&a, push_value);
        StackDamp(&a);

        scanf("%lf", &push_value);
        StackPush(&a, push_value);
        StackDamp(&a);

        scanf("%lf", &push_value);
        StackPush(&a, push_value);
        StackDamp(&a);

        StackDamp(&a);
        poped_value = StackPop(&a);
        printf("Poped value = %.3lf\n", poped_value);
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
        printf("\nStack info\n");
        printf("Stack size = %d\n\n", st->size);

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



