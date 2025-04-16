#include <stdio.h>

int main()
{
    int arr[10];
    int max;
    int min;
    int sum = 0;
    float avg = 0.0;
    printf("请输入十个学员成绩：");
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    max = arr[0];
    min = arr[0];
    for (int i = 0; i < 10; i++)
    {
        if (arr[i] < 60)
        {
            printf("输出不及格学员的成绩为：%d，下标为：%d\n", arr[i], i);
        }
        max = max > arr[i] ? max : arr[i];
        min = min < arr[i] ? min : arr[i];
    }
    avg = sum / 10.0;
    for (int i = 0; i < 10; i++)
    {
        if (max == arr[i])
        {
            printf("最高分的下标为：%d\n", i);
        }
        if (min == arr[i])
        {
            printf("最低分的下标为：%d\n", i);
        }
    }
    printf("总成绩：%d，平均成绩：%.2f\n", sum, avg);
    return 0;
}
