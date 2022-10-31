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






