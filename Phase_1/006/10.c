#include <stdio.h>
#include <string.h>

void my_cmp(char a[], int n1, char b[], int n2)
{
    int i;
    for (i = 0; i < n1 && i < n2; i++)
    {
        if (a[i] < b[i])
        {
            printf("str a < str b\n");
            return;
        }
        if (a[i] > b[i])
        {
            printf("str a > str b\n");
            return;
        }
    }

    // 如果前面的字符都相等，比较字符串长度
    if (n1 < n2)
    {
        printf("str a < str b\n");
    }
    else if (n1 > n2)
    {
        printf("str a > str b\n");
    }
    else
    {
        printf("str a == str b\n");
    }
}

int main()
{
    char a[] = "hello world";
    char b[] = "hello";
    my_cmp(a, strlen(a), b, strlen(b));
    return 0;
}
