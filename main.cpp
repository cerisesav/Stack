#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "error.h"
#include "processor.h"

int main()
{
    struct Stack stk = {};
    struct Stack *ptr_stk;
    ptr_stk = &stk;

    StackCtor(ptr_stk);

    read(ptr_stk);

    StackDtor(ptr_stk);
}
