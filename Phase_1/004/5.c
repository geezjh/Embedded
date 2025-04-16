/***********************************************************
  > File Name: 5.c
  > Author: rose
  > Mail: 483086134@qq.com
  > Created Time: 2025年01月17日 星期五 20时27分22秒
    > Modified Time:2025年01月17日 星期五 20时35分29秒
 *******************************************************/

#include <stdio.h>
#define PI 3.141592

int main()
{
    float area;
    for(int i =1;i<=10;i++){
       area = i*i*PI;
       if(area>100.00)
            break;
        printf("r=%d,area=%.2f\n",i,area);
    }
    return 0;
}

