#include<stdio.h>
#include<math.h>

int main()
{
	int a,b,c;
	printf("请输入三角形的边长：");
	scanf("%d %d %d",&a,&b,&c);
	float s = (a+b+c)/2.0;
	float temp = s*(s-a)*(s-b)*(s-c);
	float result = sqrt(temp);
	printf("海伦公式计算的三角形面积为：%.2f\n",result);	
	return 0;
}
