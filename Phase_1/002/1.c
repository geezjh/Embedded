#include<stdio.h>

int main()
{
    printf("short的内存空间是%lu\nint的内存空间是%lu\nlong的内存空间是%lu\nfloat的内存空间是%lu\ndouble的内存空间是%lu\nchar的内存空间是%lu\n",sizeof(short),sizeof(int),sizeof(long),sizeof(float),sizeof(double),sizeof(char));
    return 0;
}