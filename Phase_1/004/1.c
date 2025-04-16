#include <stdio.h>

int main()
{
    int n;
    int sum = 0;
    printf("please input a number: ");
    scanf("%d",&n);
    for(int i=1;i<=n;i+=2){
        sum+=i;
    }
    printf("%d以内所有的奇数和为:%d\n",n,sum);
    return 0;
}
