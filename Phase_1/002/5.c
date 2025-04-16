#include <stdio.h>

int main()
{
    float hight, weight, bmi;
    printf("Enter your hight and weight: ");
    scanf("%f %f", &hight, &weight);
    bmi = weight / (hight * hight);
    printf("Your BMI is %f\n", bmi);
    return 0;
}