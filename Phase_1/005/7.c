#include <stdio.h>

int main()
{
    int arr[3][3];
    int sum = 0;
    printf("请输入一个二维数组(3x3):\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &arr[i][j]);
            if (i >= j)
            {
                sum += arr[i][j];
            }
        }
    }
    printf("下三角元素的和为：%d\n", sum);
    return 0;
}