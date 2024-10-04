#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int main()
{
    struct Stack stk = {};
    struct Stack *ptr_stk;
    ptr_stk = &stk;
    StackElem_t DeletedValue = 0;
    StackCtor(ptr_stk);

    // for (int i = 0; i < 30; i++)
    // {
    //     StackPush(ptr_stk, i * i);
    // }

    StackPush(ptr_stk, 1);
    // for (size_t i = 0; i < ptr_stk->size; i++) {
    //     printf("\tdata[%zu] = %lf\n", i, ptr_stk->data[i]);
    // }
    StackPush(ptr_stk, 2);
    // for (size_t i = 0; i < ptr_stk->size; i++) {
    //     printf("\tdata[%zu] = %lf\n", i, ptr_stk->data[i]);
    // }
    StackPop(ptr_stk, &DeletedValue);

    StackDtor(ptr_stk);
}
