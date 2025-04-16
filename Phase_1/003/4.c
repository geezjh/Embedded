#include<stdio.h>

int main()
{
    int a,b;
    printf("请输入两个数：");
    scanf("%d %d",&a,&b);
    if(a == b){
        printf("%d等于%d\n",a,b);
    }else if(a > b){
        printf("最大数为%d\n",a);
    }else{
        printf("最大数为%d\n",b);
    }
    return 0;
}