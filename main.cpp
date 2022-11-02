#include  "stack.h"

int main()
{   
    Stack stack = {};

    StackCtor(&stack);
    StackPrint(&stack);
    StackConsoleWork(&stack);
    StackDtor(&stack);
    StackPrint(&stack);

    free(stack.data);
    return 0;
}









