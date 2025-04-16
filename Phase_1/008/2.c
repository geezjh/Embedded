// 设计一个描述商品的结构体，存放一个商品信息，并显示
#include <stdio.h>
struct info
{
    int no;
    char name[20];
    float price;
} goods = {1, "笔记本", 30.00};

int main()
{
    printf("%s的序号为：%d,价格为：%.2f\n", goods.name, goods.no, goods.price);
    return 0;
}