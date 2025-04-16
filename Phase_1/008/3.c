// （1）存储多个商品的信息，后显示
// （2）查询价格最高的商品的信息
// （3）用静态分配（结构体变量）和动态分配分别实现。
// #include <stdio.h>
// struct info
// {
//     int no;
//     char name[20];
//     float price;
// } goods[3] = {1, "笔记本", 30.00, 2, "钢笔", 15.00, 3, "试题册", 35.00};

// int main()
// {
//     float max_price = goods[0].price;
//     int k;
//     for (int i = 0; i < 3; i++)
//     {
//         printf("%s的序号为：%d,价格为：%.2f\n", goods[i].name, goods[i].no, goods[i].price);
//         if (max_price < goods[i].price)
//         {
//             max_price = goods[i].price;
//             k = i;
//         }
//     }
//     printf("价格最高的商品的信息为:%s的序号为：%d,价格为：%.2f\n", goods[k].name, goods[k].no, goods[k].price);
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
struct info
{
    int no;
    char name[20];
    float price;
};
int main()
{
    struct info *goods = (struct info *)calloc(3, sizeof(struct info));
    if (goods == NULL)
    {
        printf("内存分配失败\n");
        return 1;
    }
    struct info *ptr = goods;
    ptr->no = 1;
    snprintf(ptr->name, sizeof(ptr->name), "笔记本");
    ptr->price = 30.00;
    ptr++;
    ptr->no = 2;
    snprintf(ptr->name, sizeof(ptr->name), "钢笔");
    ptr->price = 15.00;
    ptr++;
    ptr->no = 3;
    snprintf(ptr->name, sizeof(ptr->name), "试题册");
    ptr->price = 35.00;
    ptr++;
    // 重置指针到数组起始位置
    ptr = goods;
    float max_price = ptr->price;
    struct info *max_goods = ptr;
    // 显示所有商品信息并找出价格最高的商品
    for (int i = 0; i < 3; i++)
    {
        printf("%s的序号为：%d,价格为：%.2f\n", ptr->name, ptr->no, ptr->price);
        if (max_price < ptr->price)
        {
            max_price = ptr->price;
            max_goods = ptr;
        }
        ptr++;
    }

    // 显示价格最高的商品信息
    printf("价格最高的商品的信息为:%s的序号为：%d,价格为：%.2f\n", max_goods->name, max_goods->no, max_goods->price);
    free(goods);
}