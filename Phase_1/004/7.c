/***********************************************************
  > File Name: 7.c
  > Author: rose
  > Mail: 483086134@qq.com
  > Created Time: 2025年01月18日 星期六 15时43分46秒
    > Modified Time:2025年01月18日 星期六 15时48分26秒
 *******************************************************/

#include <stdio.h>

int main()
{
    for(int i=0;i<100;i++){
        if(i%7==0 && i!=0)
            continue;
        printf("%d\t",i);
    }
    printf("\n");
    return 0;
}


