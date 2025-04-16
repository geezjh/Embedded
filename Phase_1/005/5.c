#include <stdio.h>

int main()
{
    int arr[3][4];
    int sum = 0;
    float avg = 0.0;
    int rowMax[3];
    int colMin[4];

    printf("请输入一个二维数组(3x4):\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scanf("%d", &arr[i][j]);
            sum += arr[i][j];
        }
    }

    avg = sum / 12.0;

    // 初始化每行最大值和每列最小值
    for (int i = 0; i < 3; i++)
    {
        rowMax[i] = arr[i][0];
    }
    for (int j = 0; j < 4; j++)
    {
        colMin[j] = arr[0][j];
    }

    // 计算每行的最大值
    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j < 4; j++) // 从第二个元素开始比较
        {
            rowMax[i] = rowMax[i] > arr[i][j] ? rowMax[i] : arr[i][j];
        }
    }

    // 计算每列的最小值
    for (int j = 0; j < 4; j++)
    {
        for (int i = 1; i < 3; i++) // 从第二个元素开始比较
        {
            colMin[j] = colMin[j] < arr[i][j] ? colMin[j] : arr[i][j];
        }
    }

    // 打印每行的最大值
    for (int i = 0; i < 3; i++)
    {
        printf("第%d行的最大值是：%d\n", i + 1, rowMax[i]);
    }

    // 打印每列的最小值
    for (int j = 0; j < 4; j++)
    {
        printf("第%d列的最小值是：%d\n", j + 1, colMin[j]);
    }

    printf("总和：%d\n", sum);
    printf("平均值：%.2f\n", avg);
    return 0;
}
