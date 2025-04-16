#include<stdio.h>

int main()
{
    int a,b,c;
    printf("请输入三个数：");
    scanf("%d %d %d",&a,&b,&c);
    if(a == b&& b == c && c == a){
        printf("输入的三个数相等值为：%d\n",a);
    }else if(a>b && b>c){
        printf("最大数为%d\n",a);
    }else if(b>a && b>c){
        printf("最大数为%d\n",b);
    }else if(c>a && c>b){
        printf("最大数为%d\n",c);
    }
    return 0;
}