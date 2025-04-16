#include <stdio.h>
#include <math.h>

int length(int n)
{
    int count = 0;
    while (n)
    {
        count++;
        n /= 10;
    }
    return count;
}

void Convert(char a[], int n, int num)
{
    int i = 0;
    while (n)
    {
        // 将整数的每一位转换为对应的字符
        a[i] = (num / (int)(pow(10, n - 1))) % 10 + '0';
        num = num % ((int)(pow(10, n - 1)));
        i++;
        n--;
    }

    a[i] = '\0'; // 确保字符串以空字符结尾
    puts(a);     // 输出整个字符串
}

int main()
{
    int n;
    printf("please input a number: ");
    scanf("%d", &n);
    int a = length(n);
    char b[a + 1];
    Convert(b, a, n); // 传递正确的数组参数
    return 0;
}
