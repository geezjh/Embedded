#include <stdio.h>
#define N 3

void count_num(int (*p)[N], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i <= j)
            {
                if (*(p[i] + j) == 0)
                {
                    count++;
                }
            }
        }
    }
    printf("上三角中0的数量为: %d\n", count);
    printf("矩阵为:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int arr[N][N] = {1, 2, 3,
                     4, 0, 6,
                     7, 8, 0};
    count_num(arr, N);
    return 0;
}
