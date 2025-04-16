#include <stdio.h>

int main()
{
    int a[3][4] = {
        {1, 12, 3, 4},
        {4, 19, 6, 7},
        {8, 29, 10, 11}};
    int i, j;
    int row_max, row_max_col;
    int col_min;
    int saddle_point_found = 0;

    for (i = 0; i < 3; i++)
    {
        row_max = a[i][0];
        row_max_col = 0;

        // 找到第 i 行的最大值及其列索引
        for (j = 1; j < 4; j++)
        {
            if (a[i][j] > row_max)
            {
                row_max = a[i][j];
                row_max_col = j;
            }
        }

        col_min = a[0][row_max_col];

        // 检查第 row_max_col 列的最小值是否等于 row_max
        for (j = 1; j < 3; j++)
        {
            if (a[j][row_max_col] < col_min)
            {
                col_min = a[j][row_max_col];
            }
        }

        // 如果 row_max 等于 col_min，则找到了鞍点
        if (row_max == col_min)
        {
            printf("鞍点=%d\t%d行%d列\n", row_max, i, row_max_col);
            saddle_point_found = 1;
        }
    }

    // 如果没有找到鞍点，打印提示信息
    if (!saddle_point_found)
    {
        printf("No saddle point found in the matrix.\n");
    }

    return 0;
}
