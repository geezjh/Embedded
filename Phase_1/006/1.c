#include <stdio.h>
#define PI 3.1415926
float area(float r)
{
    float res = 0;
    res = 4 * r * r * PI;
    return res;
}

int main()
{
    float num;
    printf("please input number:");
    scanf("%f",&num);
    float res = area(num);
    printf("球的面积为：%.2f\n",res);
    return 0;
}