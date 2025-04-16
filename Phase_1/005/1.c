/***********************************************************
  > File Name: 1.c
  > Author: rose
  > Mail: 483086134@qq.com
  > Created Time: 2025年01月20日 星期一 19时01分36秒
    > Modified Time:2025年01月20日 星期一 19时02分34秒
 *******************************************************/

#include <stdio.h>

int main()
{
  int num;
  int arr[10];
  printf("请输入十个数：");
  for (int i = 0; i < 10; i++)
  {
    scanf("%d",&arr[i]);
  }
  printf("请输入一个数：");
  scanf("%d", &num);
  for (int i = 0; i < 10; i++)
  {
    if (num == arr[i])
      printf("这个数的下标为：%d\n", i);
  }
  return 0;
}
