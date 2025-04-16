#include <stdio.h>
#include <math.h>

float distance(int x1,int y1,int x2,int y2)
{
    float dis = sqrt((x2*x2-2*x2*x1+x1*x1)+(y2*y2-2*y2*y1+y1*y1));
    return dis;
}

int main()
{
    int x1,y1,x2,y2;
    printf("please input four data:");
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    float dis = distance(x1,y1,x2,y2);
    printf("%.2f\n",dis);
    return 0;
}
