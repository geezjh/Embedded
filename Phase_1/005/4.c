#include <stdio.h>

int main()
{
    int num;
    int arr[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    printf("二维数组初值：\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
    printf("Please input a number:");
    scanf("%d", &num);
    int found = 0; // 添加变量来标识是否找到数字
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (num == arr[i][j])
            {
                printf("你输入的数为：%d,行列位置为：%d行%d列\n", num, i, j);
                found = 1; // 找到数字后设置标识
                break;     // 找到数字后跳出内层循环
            }
        }
        if (found)
            break; // 找到数字后跳出外层循环
    }
    if (!found) // 如果没有找到
    {
        printf("没找到你输入的数\n");
    }
    return 0;
}
