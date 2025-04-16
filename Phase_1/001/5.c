#include<stdio.h>

int main()
{
	for(int i=0;i<=2;i++)
	{
		for(int j=0;j<=i;j++)
		{	
			printf("* ");
		}
	printf("\n");
	}
	for(int i=2;i>0;i--)
	{
		for(int j=1;j<=i;j++)
		{
			printf("* ");
		}
	printf("\n");
	}
	return 0;
}
