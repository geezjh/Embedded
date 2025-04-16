// 自行查找fscanf和fprintf函数，并尝试用这两个函数进行数据的保存和读取。
// scanf("格式控制符"， 地址列表)
// printf("格式控制符"，输出列表)
// fscanf（文件指针，"格式控制符"，地址列表）
// fprintf（文件指针，"格式控制符"，输出列表)
#include <stdio.h>

#define NUM_COUNT 5

int main()
{
    FILE *fp;
    int numbers[NUM_COUNT];
    int read_numbers[NUM_COUNT];
    int i;

    // 打开文件以写入数据
    fp = fopen("1.txt", "w");
    if (fp == NULL)
    {
        printf("文件打开失败");
        return 1;
    }

    // 从用户输入读取数据
    printf("请输入 %d 个整数：\n", NUM_COUNT);
    for (i = 0; i < NUM_COUNT; i++)
    {
        scanf("%d", &numbers[i]);
        // 使用 fprintf 将数据写入文件
        fprintf(fp, "%d ", numbers[i]);
    }

    // 关闭文件
    fclose(fp);

    // 打开文件以读取数据
    fp = fopen("1.txt", "r");
    if (fp == NULL)
    {
        printf("文件打开失败");
        return 1;
    }

    // 使用 fscanf 从文件读取数据
    for (i = 0; i < NUM_COUNT; i++)
    {
        if (fscanf(fp, "%d", &read_numbers[i]) != 1)
        {
            printf("读取文件时出错\n");
            fclose(fp);
            return 1;
        }
    }

    // 关闭文件
    fclose(fp);

    // 显示从文件中读取的数据
    printf("从文件中读取的 %d 个整数为：\n", NUM_COUNT);
    for (i = 0; i < NUM_COUNT; i++)
    {
        printf("%d ", read_numbers[i]);
    }
    printf("\n");

    return 0;
}