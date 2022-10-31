#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef double stack_type;
typedef struct
{
    stack_type * data;
    size_t capacity;
    size_t size;
    size_t error_code;

}Stack;

const double POISON_VALUE = NAN;

const size_t MAX_LINE_COMMAND = 5;

enum error_list
{
    ERR_NULL_DATA = 1,
    ERR_OUT_OF_STACK = 2
};

void StackInit(Stack * st, size_t capacity);

void StackPush(Stack * st, stack_type push_value);

//int StackCheck(Stack * st);

void StackDump(Stack * st);

stack_type StackPop(Stack * st);

void StackMul(Stack * st);

void StackSub(Stack * st);

void StackDiv(Stack * st);

void StackPrint(Stack * st);

void StackLogic(Stack * st, char * command, stack_type push_value);

void StackAdd(Stack * st);

void StackConsoleWork(Stack * st);


#endif // STACK_H
