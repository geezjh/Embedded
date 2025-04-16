#include<stdio.h>

int main()
{
	int a;
	float b;
	printf("请输入你的年龄和身高：");
	scanf("%d %f",&a,&b);
	printf("我的年龄是%d岁,身高是%.2fcm\n",a,b);
	return 0;
}
