#include <stdio.h>
#include <stdint.h>

uint32_t reverse(uint32_t x)
{
    x = ((x & 0x55555555u) << 1) + ((x >> 1) & 0x55555555u);
    x = ((x & 0x33333333u) << 2) + ((x >> 2) & 0x33333333u);
    x = ((x & 0x0f0f0f0fu) << 4) + ((x >> 4) & 0x0f0f0f0fu);
    x = ((x & 0x00ff00ffu) << 8) + ((x >> 8) & 0x00ff00ffu);
    x = ((x & 0x0000ffffu) << 16) + ((x >> 16) & 0x0000ffffu);
    return x;
}
void print_binary(uint32_t v)
{
    unsigned int mask=1<<((sizeof(int)<<3)-1);
    while(mask) {
        printf("%d", (v&mask ? 1 : 0));
        mask >>= 1;
    }
    printf("\n");
}
// для вывода цикл можно
int main()
{
    uint32_t x = 0b010100;
    uint32_t y = 0b1001;
    // printf("%X\n", x - y);
    // uint32_t a = reverse(x);
    // print_binary(x-y);
    // printf("%d\n", x - y);
    // printf("%d\n", ((x-y) >> 31)&1);
    // int64_t sign = ((x-y) >> 31)&1;
    // printf("%d", (sign*y)+(1-sign)*x);
    print_binary(x);
    print_binary(-x);
    print_binary(x & -x);
//     uint32_t right_one_digit = a & (~(a - 1));
//     uint32_t palindrom = reverse(x) / right_one_digit;
//
//     print_binary(x);
//     printf("\n");
//     print_binary(palindrom);
//     printf("\n");
//
//     printf("%u", !(palindrom ^ x));
}
