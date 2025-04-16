// 从键盘输入一串字符，存放到一个文件中，后打开读取存到内存另一个空间并显示，验证是否正确
// 键盘接收-->存放到文件-->读文件-->显示内容
#include <stdio.h>
#define MAX_LENGTH 1000
int main()
{
    FILE *fp = fopen("1.txt", "w+");
    if (fp == NULL)
    {
        printf("无法打开文件\n");
        return 1;
    }
    char input[MAX_LENGTH];
    char buf[MAX_LENGTH];
    printf("请输入一串字符：");
    fgets(input, MAX_LENGTH, stdin);
    fputs(input, fp);
    fseek(fp, 0, SEEK_SET);
    fgets(buf, MAX_LENGTH, fp);
    fclose(fp);
    printf("从文件中读到的内容为：%s\n", buf);
    return 0;
}