#include<stdio.h>

int fh(int x){
    return x;
}
int main()
{
    int num;
    printf("please input number:");
    scanf("%d",&num);
    int x = fh(num);
    printf("%d\n",x);
    return 0;
}
