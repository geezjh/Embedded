/***********************************************************
  > File Name: 8.c
  > Author: rose
  > Mail: 483086134@qq.com
  > Created Time: 2025年01月18日 星期六 15时48分30秒
    > Modified Time:2025年01月18日 星期六 15时52分11秒
 *******************************************************/

#include <stdio.h>

int main()
{
    for(int i=1;i<10;i++){
        for(int j=1;j<=i;j++){
            printf("%d*%d=%d\t",j,i,j*i);
        }
        printf("\n");
    }
    return 0;
}

