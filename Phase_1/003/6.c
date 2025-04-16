#include <stdio.h>

int main()
{
    float hight, weight, bmi;
    printf("请输入身高和体重: ");
    scanf("%f %f", &hight, &weight);
    bmi = weight / (hight * hight);
    printf("Your BMI is %.1f\n", bmi);
    if (bmi < 18.5)
        printf("偏瘦，注意加强营养\n");
    else if (bmi < 23.9)
        printf("体重指数良好，注意保持\n");
    else
        printf("你有点偏胖，注意锻炼\n");
    return 0;
}
