/***********************************************************
  > File Name: 10.c
  > Author: rose
  > Mail: 483086134@qq.com
  > Created Time: 2025年01月18日 星期六 16时03分10秒
    > Modified Time:2025年01月18日 星期六 16时16分38秒
 *******************************************************/

#include <stdio.h>

int main()
{
    int a, b, c;
    for(int i = 100; i < 1000; i++){
        a = i / 100;
        b = (i / 10) % 10;  
        c = i % 10;        
        if((a*a*a + b*b*b + c*c*c) == i){
            printf("%d\t", i);
        }
    }
    printf("\n");
    return 0;
}

