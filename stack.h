#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef double stack_type;
typedef struct
{   
    void* stack_pointer = nullptr; // the pointer to the calloced memory block
    stack_type* data = nullptr; // the pointer to the stack's data
    size_t capacity = 0; // the number of elements in the stack
    size_t next_empty_cell = 0; // the pointer to the next empty cell of the stack's data
    size_t error_code = 0; // the error code of stack
    size_t hash = 0; // the value used in oreder to validate actions with the stack
    size_t* left_canary_position = nullptr; // the pointer to the left canary 
    size_t* right_canary_position = nullptr; // the pointer to the right canary
}Stack;

const double POISON_VALUE = NAN; // the poison value 

const size_t MAX_LINE_COMMAND = 5; // the maximum length of the command string
const size_t CANARY = 0xDEAD; // the canary value

enum error_list_codes 
{
    ERR_NULL_DATA = 1,
    ERR_OUT_OF_STACK_RIGHT = 2,
    ERR_OUT_OF_STACK_LEFT = 3,
    ERR_LEFT_CANARY_DEAD = 4,
    ERR_RIGHT_CANARY_DEAD = 5,
    ERR_HASH_CHANGED = 6,
    STACK_IS_OK = 0
};

const char* Enum_to_string(size_t code); // converts an enum's int value to the enum's string value

void StackCtor(Stack* st); // creates and initializes stack

void StackPush(Stack* st, stack_type push_value); // gets the value and pushes in to the stack

void StackCheck(Stack* st,  const char * FUNCT_NAME, int FUNCT_LINE); // checks the stack for the possible errors

void StackDtor(Stack* st); // deletes the stack and spoils all stack's data with the poison value

void StackDump(Stack* st,  const char * FUNCT_NAME, int FUNCT_LINE); // outputs the data to the LOG.txt about the stack

void StackPop(Stack* st); // deletes the value from the stack

void StackMul(Stack* st); // multiplies two values of the stack

void StackSub(Stack* st);  // substracts one value of the stack from another one 

void StackDiv(Stack* st); // divides the preceding element by the last element of the stack

void StackPrint(Stack* st); // prints the stack's current structure in the console

void StackLogic(Stack* st, char* command, stack_type push_value); // calls other functions depending on the entered command 

void StackAdd(Stack* st); // adds the entered value to next empty memory cell of the stack

void StackConsoleWork(Stack* st); // supports the work of program until 'HLT' was entered in the console

void StackRealocUp(Stack* st); // increases the capacity of the stack, reallocs data

void StackRealocDown(Stack* st); // decreases the capacity of the stack, reallocs data

void Calculate_hash(Stack* st); // recalculates the value of hash everytime when called

size_t Get_cur_value_of_hash(Stack* st); // calculates the current value of the hash 


#endif // STACK_H
