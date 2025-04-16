#include <stdio.h>
int find_Str(char a[], int n, char b)
{
    int k;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == b)
        {
            k = i;
        }
    }
    return k;
}
int main()
{
    char str[13] = "hello world";
    char a;
    printf("请输入一个字符");
    scanf("%c", &a);
    int k = find_Str(str, 10, a);
    printf("该字符的位置为%d\n", k);
    return 0;
}