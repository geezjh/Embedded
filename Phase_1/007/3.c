#include <stdio.h>

int main()
{
    int a = 1;
    char b = 'b';
    float c = 3.0;
    int *p = &a;
    char *q = &b;
    float *z = &c;
    printf("整型指针变量的大小为:%zu\n", sizeof(p));
    printf("字符型指针变量的大小为:%zu\n", sizeof(q));
    printf("浮点型指针变量的大小为:%zu\n", sizeof(z));
    return 0;
}