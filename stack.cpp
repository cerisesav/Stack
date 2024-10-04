#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// canary
// void *

#include "stack.h"

CodeError StackPush(Stack* stk, StackElem_t elem)
{
    #ifdef CANARY
        StackAssert(stk);
    #endif

    if (stk->size >= stk->capacity)
        stk->data = SizeUpStack(stk);

    else
    {
        stk->data[stk->size] = elem;
        stk->size++;
    }

    #ifdef CANARY
        StackAssert(stk);
    #endif

    return stk->err;
}

CodeError StackPop(Stack* stk, StackElem_t* DeletedValue)
{
    #ifdef CANARY
        StackAssert(stk);
    #endif

    if (stk->size > 0)
    {
        *DeletedValue = stk->data[--stk->size];

        if (stk->capacity/stk->size > 2)
            stk->data = SizeDownStack(stk);
        printf("Deleted Value: %lg\n", *DeletedValue);
    }
    else
    {
        stk->err = Underflow;
    }
    #ifdef CANARY
        StackAssert(stk);
    #endif

    return stk->err;
}


void StackCtor(Stack* stk)
{
    #ifdef CANARY

    stk->LEFT_CANARY = CANARY_VALUE;
    stk->RIGHT_CANARY = CANARY_VALUE;

    #endif
    stk->capacity = 10;
    int size = 0;

    #ifdef CANARY
        size = stk->capacity * sizeof(StackElem_t) + 2 * sizeof(Canary_t);
    #else
        size = stk->capacity * sizeof(StackElem_t);
    #endif

    if (stk->capacity == 0)
    {
        stk->data = nullptr;
    }

    else
    {
        stk->data = (StackElem_t*)calloc(size, 1);
        if (!stk->data) {
            stk->err = NullPointer;
        }
    }

    #ifdef CANARY
    stk->data = (StackElem_t*)((Canary_t*)stk->data + 1);

    *((Canary_t*)stk->data - 1) = CANARY_VALUE;
    *((Canary_t*)stk->data + stk->capacity) = CANARY_VALUE;
    #endif
    stk->size = 0;

    stk->err = NoError;
    StackAssert(stk);
}


void StackDtor(Stack* stk)
{
    if (stk->data)

    #ifdef CANARY
    {
        free((Canary_t*)stk->data - 1);
        stk->data = nullptr;
    }
    #else
    {
        free(stk->data);
        stk->data = nullptr;
    }
    #endif

    stk->size = -1;
    stk->capacity = -1;
}


void StackDump(struct Stack* stk, const char *file, int line, const char *function)
{
    printf("\nTime is %s\n", __TIME__);
    printf("StackDump called from %s (%d) %s\n", function, line, file);
    printf("Stack[%p] \"stk\" in function - %s.\n\n", (void*)stk, function);

    printf("--------------------------------------------------------------------------\n");
    printf("Struct:\n");
    printf("\tsize = %d\n", stk->size);
    printf("\tcapacity = %zu\n", stk->capacity);
    printf("\tAddress of data[] = %p\n", (void*)stk->data);

    for (size_t i = 0; i < stk->size; i++) {
        printf("\tdata[%zu] = %lf\n", i, stk->data[i]);
    }

    printf("--------------------------------------------------------------------------\n");
}

void StackAssert(Stack* stk)
{
    if (stk->err != NoError)
    {
        printf("Error: %s\n", StackError(stk));
        StackDumpMacro(stk);
        assert(0);
    }

    StackDumpMacro(stk);
}


StackElem_t* SizeUpStack(Stack* stk)
{

    if (stk->size > 1000)
        stk->capacity *= 1.05;
    else if (stk->size > 100)
        stk->capacity *= 1.1;
    else
        stk->capacity += 10;

    #ifdef CANARY
        size_t new_size = stk->capacity * sizeof(StackElem_t) + 2 * sizeof(Canary_t);
        stk->data = (StackElem_t*)realloc((Canary_t*)stk->data - 1, new_size);
    #else
        stk->data = (StackElem_t*)realloc(stk->data, stk->capacity);
    #endif

    if (!stk->data)
        return NULL;

    #ifdef CANARY
        stk->data = (StackElem_t*)((Canary_t*)stk->data + 1);
        *((Canary_t*)stk->data - 1) = CANARY_VALUE;
        *((Canary_t*)stk->data + stk->capacity) = CANARY_VALUE;
    #endif

    return stk->data;
}


StackElem_t* SizeDownStack(Stack* stk)
{
    if (stk->size > 10)
        stk->capacity *= 0.6;
    else
        stk->capacity -= 1;

    #ifdef CANARY
        size_t new_size = stk->capacity * sizeof(StackElem_t) + 2 * sizeof(Canary_t);
        stk->data = (StackElem_t*)realloc((Canary_t*)stk->data - 1, new_size);
    #else
        stk->data = (StackElem_t*)realloc(stk->data, stk->capacity);
    #endif

    if (!stk->data)
        return NULL;

    #ifdef CANARY
        stk->data = (StackElem_t*)((Canary_t*)stk->data + 1);
        *((Canary_t*)stk->data - 1) = CANARY_VALUE;
        *((Canary_t*)stk->data + stk->capacity) = CANARY_VALUE;
    #endif

    return stk->data;
}

const char* StackError(Stack* stk)
{
    switch (stk->err)
    {
        case Overflow: return "Stack Overflow";
        case Underflow: return "Stack Underflow";
        case NoError: return "Stack is working fine";
        case NullPointer: return "Null Pointer Error";
        case CanaryError: return "Canary was poisoned";
        default: return "Unknown Error";
    }
}
