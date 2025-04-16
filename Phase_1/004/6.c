/***********************************************************
  > File Name: 6.c
  > Author: rose
  > Mail: 483086134@qq.com
  > Created Time: 2025年01月17日 星期五 20时36分39秒
    > Modified Time:2025年01月17日 星期五 20时48分15秒
 *******************************************************/

#include <stdio.h>

int main()
{
    int i, count = 0, sum = 0;  // 初始化count和sum
    float avg;
    int num[10];
    for(i = 0; i < 10; i++){    
        scanf("%d", &num[i]);
    }
    for(i = 0; i < 10; i++){    
        int n = num[i];
        if(n < 0)
            continue;
        else
            count++;
        sum += n;
    }
    if(count > 0){              // 确保count不为0
        avg = (float)sum / count;  // 确保sum是float类型以得到精确的结果
        printf("正数的个数为%d, 平均数为%.2f\n", count, avg);
    } else {
        printf("没有输入正数。\n");
    }
    return 0;
}

