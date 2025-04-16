#include <stdio.h>
#define N 3

int* max_num(int (*p)[N], int n)
{
    int max = p[0][0]; // 初始化为数组的第一个元素
    int* max_ptr = &p[0][0]; // 初始化为数组的第一个元素的地址
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (max < *(p[i] + j))
            {
                max = *(p[i] + j);
                max_ptr = &(p[i][j]); // 更新最大元素地址
            }
        }
    }
    return max_ptr;
}

int main()
{
    int arr[N][N] = {1, 2, 3,
                     4, 0, 6,
                     7, 8, 0};
    int* a = max_num(arr, N); // 修改返回值类型为指针类型
    printf("二维数组中最大元素的地址为：%p\n", (void*)a); // 修改打印格式，注意强制转换为void*
    return 0;
}
