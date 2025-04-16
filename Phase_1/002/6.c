#include <stdio.h>

int main()
{   
    float Celsius,Fahrenheit;
    printf("please input Celsius:");
    scanf("%f",&Celsius);
    printf("Fahrenheit is %f\n",Celsius * 1.8 + 32);
    return 0;
}