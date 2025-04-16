/***********************************************************
  > File Name: 2.c
  > Author: rose
  > Mail: 483086134@qq.com
  > Created Time: 2025年01月17日 星期五 19时52分59秒
    > Modified Time:2025年01月17日 星期五 20时02分26秒
 *******************************************************/

#include <stdio.h>

int main()
{
    int i;
    double sum = 1.00; 
    double term; 
    for(i = 2; ; i++){ 
        term = 1.0 / (i * (i + 1));
        if(term < 0.00001) 
            break;
        sum += term;
    }
    printf("sum=%.2f\n", sum);
    return 0;
}


