#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "error.h"
#include "processor.h"

void read(Stack* stk)
{
    FILE *file = fopen("commands.txt", "r");

    if (file == NULL)
    {
        fprintf(stderr, "Failed to open the file\n");
        assert(0);
    }

    assembler(file);

    FILE *asmcommand;
    asmcommand = fopen("command.asm", "r");

    if (asmcommand == NULL) {
        printf("Не удалось открыть файл.\n");
        assert(0);
    }

    long size = return_size_text(asmcommand);
    int code[size];

    rewind(asmcommand);

    for (size_t i = 0; i < size; i++)
        fscanf(asmcommand, "%d", &code[i]);

    rewind(asmcommand);

    fclose(file);
    Run(code, stk, size);
}

void Run(int* code, Stack* stk, long size)
{
    int ip = 0;

    while (ip < size)
    {
        switch (code[ip])
        {
            case PUSH:
                StackPush(stk, code[ip+1]);
                ip += 2;
                break;

            case ADD:
                add(stk);
                ip += 1;
                break;

            case POP:
                StackPopV(stk);
                ip+=1;
                break;

            case HLT:
                ip+=1;
                break;

            case SUB:
                sub(stk);
                ip+=1;
                break;

            case JMP:
                ip = code[ip+1];
                break;

            case JA:
                if (ip > code[ip+1])
                    ip = code[ip+1];
                else
                    ip += 2;
                break;

            case JAE:
                if (ip >= code[ip+1])
                    ip = code[ip+1];
                else
                    ip += 2;
                break;

            case JB:
                if (ip < code[ip+1])
                    ip = code[ip+1];
                else
                    ip += 2;
                break;

            case JBE:
                if (ip <= code[ip+1])
                    ip = code[ip+1];
                else
                    ip += 2;
                break;

            case JE:
                if (ip == code[ip+1])
                    ip = code[ip+1];
                else
                    ip += 2;
                break;

            case JNE:
                if (ip != code[ip+1])
                    ip = code[ip+1];
                else
                    ip += 2;
                break;

            default:
                printf("%d aoaooaoao ", code[ip]);
                ip += 1;
                break;
        }
    }

    StackDumpMacro(stk);
}

void add(Stack* stk)
{
    int a = StackPopV(stk);
    int b = StackPopV(stk);

    int sum = a + b;

    StackPush(stk, sum);
}

void sub(Stack* stk)
{
    int a = StackPopV(stk);
    int b = StackPopV(stk);

    int sub = a - b;

    StackPush(stk, sub);
}

void mul(Stack* stk)
{
    int a = StackPopV(stk);
    int b = StackPopV(stk);

    int mul = a * b;

    StackPush(stk, mul);
}

void div(Stack* stk)
{
    int a = StackPopV(stk);
    int b = StackPopV(stk);

    int div = a / b;

    StackPush(stk, div);
}

const long return_size_text(FILE *commands)
{
    size_t count = 0;
    int curDigit = 0;

    while(fscanf(commands, "%d", &curDigit) != EOF)
        count++;
    if(!feof(commands))
        puts("Errror!");
    return count;
}

void assembler(FILE* command)
{
    FILE* asmcommand = fopen("command.asm", "a");
    size_t len = 0;
    char cmd[100] = " ";
    ssize_t read;

    while (fscanf(command, "%s", cmd) == 1)
    {

        if (strcmp(cmd, "push") == 0)
        {
            fputs("1 ", asmcommand);

            int arg = 0;

            fscanf(command, "%d", &arg);
            fprintf(asmcommand, "%d ", arg);

        }
        else if (strcmp(cmd, "add") == 0)
        {
            fputs("2 ", asmcommand);
        }

        else if (strcmp(cmd, "pop") == 0)
        {
            fputs("3 ", asmcommand);
        }

        else if (strcmp(cmd, "sub") == 0)
        {
            fputs("4 ", asmcommand);
        }

        else if (strcmp(cmd, "jmp") == 0)
        {
            fputs("0 ", asmcommand);
        }

        else if (strcmp(cmd, "hlt") == 0)
        {
            fputs("-666 ", asmcommand);
        }
    }

    fclose(asmcommand);
}

