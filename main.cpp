#include  "stack.h"

int main()
{   
    Stack stack = {};

    StackCtor(&stack);
    StackPrint(&stack);
    StackConsoleWork(&stack);
    StackDtor(&stack);

    return 0;
}









