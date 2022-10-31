#include  "stack.h"

int main()
{
    Stack stack = {.capacity = 0, .size = 0, .error_code = 0};

    StackInit(&stack, 5);

    StackPrint(&stack);

    StackConsoleWork(&stack);
    StackDump(&stack);

    free(stack.data);
    return 0;
}









