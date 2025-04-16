// 编写一个函数，用指针变量做参数，用于求出一个浮点型数组元素的平均值。
#include <stdio.h>

void average(float *p, int n)
{
    float sum = 0, aver;
    float *q = p;
    for (; q < (p + n); q++)
    {
        sum += *q;
    }
    aver = sum / n;
    printf("average=%.2f\n", aver);
}
int main()
{
    float a[10] = {1.23, 4.56, 7.89, 10.11, 12.13, 14.15, 16.17, 18.19, 20.21, 22.22};
    average(a, 10);
    return 0;
}