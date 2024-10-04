#ifndef STACK_H
#define STACK_H
#define StackDumpMacro(stk) (StackDump(stk, __FILE__, __LINE__, __FUNCTION__))
typedef double StackElem_t;
typedef uint64_t Canary_t;
#define CANARY_VALUE 0xDEAD
#define FILL_VALUE -666
// #define CANARY

enum CodeError {
    Overflow,
    Underflow,
    NullPointer,
    CanaryError,
    NoError
};

struct Stack
{
    Canary_t LEFT_CANARY;
    StackElem_t* data;
    int size;
    size_t capacity;
    CodeError err;
    Canary_t RIGHT_CANARY;
};

CodeError StackPush(Stack* stk, StackElem_t elem);

CodeError StackPop(Stack* stk, StackElem_t* DeletedValue);

void StackCtor(Stack* stk);

void StackDtor(Stack* stk);

void StackAssert(Stack* stk);

const char* StackError(Stack* stk);

StackElem_t* SizeUpStack(Stack* stk);

StackElem_t* SizeDownStack(Stack* stk);

void StackDump(struct Stack* stk, const char *file, int line, const char *function);

#endif
