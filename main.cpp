#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "error.h"

int main()
{
    struct Stack stk = {};
    struct Stack *ptr_stk;
    ptr_stk = &stk;
    StackElem_t DeletedValue = 0;

    StackCtor(ptr_stk);

    for (int j = 0; j < 30; j++)
    {
        StackPush(ptr_stk, j * j);
    }

    StackDtor(ptr_stk);
}
