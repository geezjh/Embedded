// 编写函数,要求用指针做形参，实现将二维数组(行列相同)的进行转置（行列数据互换）：
//  int(*p)[N]
#include <stdio.h>
#define N 3

void transposition(int (*p)[N], int (*q)[N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < N; j++)
        {
            *(*(q + j) + i) = *(*(p + i) + j);
        }
    }
}
int main()
{
    int arr[N][N] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int tran[N][N];
    transposition(arr, tran, N);
    printf("转置前数组为：\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
    printf("转置后数组为：\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d\t", tran[i][j]);
        }
        printf("\n");
    }
    return 0;
}