/***********************************************************
  > File Name: 2.c
  > Author: rose
  > Mail: 483086134@qq.com
  > Created Time: 2025年01月20日 星期一 19时10分18秒
    > Modified Time:2025年01月20日 星期一 19时10分37秒
 *******************************************************/

#include <stdio.h>

int main()
{
  int temp;
  int arr[10];
  printf("请输入十个数：");
  for (int i = 0; i < 10; i++)
  {
    scanf("%d", &arr[i]);
  }
  for (int i = 0; i < 10; i++)
  {
    for (int j = 1; j < 10-i; j++)
    {
        if (arr[j-1]<arr[j])
        {
            temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
        }
    }
  }
  for (int i = 0; i < 10; i++)
  {
      printf("%d\t",arr[i]);
  }
  printf("\n");
  return 0;
}
