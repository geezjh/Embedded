/***********************************************************
  > File Name: 4.c
  > Author: rose
  > Mail: 483086134@qq.com
  > Created Time: 2025年01月17日 星期五 20时22分23秒
    > Modified Time:2025年01月17日 星期五 20时25分43秒
 *******************************************************/

#include <stdio.h>

int main()
{
    int n;
    int sum = 1;
    printf("please input a number:");
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        sum*=i;
    }
    printf("%d！的结果为：%d\n",n,sum);
    return 0;
}

