#include <stdio.h>
#include <stdbool.h>

bool is_palindrome_number(int num)
{
  if (num < 0)
  {
    return false;
  }

  int original_num = num;
  int reversed_num = 0;

  while (num > 0)
  {
    int digit = num % 10;                     // 取当前数字的最后一位
    reversed_num = reversed_num * 10 + digit; // 将最后一位添加到反转数字的末尾
    num /= 10;                                // 去掉当前 数字的最后一位
  }

  return original_num == reversed_num; // 比较原始数字和反转后的数字
}

int main()
{
  int i;
  for (i = 1; i <= 10000; i++)
  {
    if (is_palindrome_number(i))
    {
      printf("%d\t", i); // 如果是回文数，打印结果
    }
  }
  printf("\n");
  return 0; // 程序正常结束
}
