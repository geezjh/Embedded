#include <stdio.h>

int flun(int x)
{
    int res = 0;
    if(x>5)
    {
        res = 4*x+7;
    }else{
        res = (-1)*2*x+3;
    }
    return res;
}
int main()
{   
    int x;
    printf("please input a number:");
    scanf("%d",&x);
    int res = flun(x);
    printf("res=%d\n",res);
    return 0;
}
