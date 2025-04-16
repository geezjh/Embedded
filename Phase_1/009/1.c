// 1、编写程序实现文件拷贝（用fgets函数实现）
#include <stdio.h>
int main()
{
    FILE *fp = fopen("1.txt", "w+");
    if (fp == NULL)
    {
        printf("无法打开文件\n");
        return 1;
    }

    // 从标准输入读取一行
    char buf[100];
    printf("请输入一行文本：");
    if (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        fprintf(fp, "%s", buf); // 将输入的文本写入文件
        printf("你输入的文本是：%s\n", buf);
    }
    else
    {
        printf("读取输入时发生错误或到达文件末尾。\n");
    }

    fclose(fp); // 关闭文件

    return 0;
}