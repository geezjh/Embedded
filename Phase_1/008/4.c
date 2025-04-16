// 开发一个简易的成绩管理系统：存储多个学员信息并处理
// 要求如下：
// （1）申请多个空间，存入学员信息
// （2）求分数最高学员姓名
// （3）求总分和平均分
// （4）统计查询
// 查询平均分以上学员的姓名
// （5）按照成绩排序
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct info
{
    char name[20];
    float score;
};
int main()
{
    struct info *stu = (struct info *)calloc(3, sizeof(struct info));
    if (stu == NULL)
    {
        printf("内存分配失败\n");
        return 1;
    }
    struct info *ptr = stu;
    snprintf(ptr->name, sizeof(ptr->name), "张三");
    ptr->score = 430.00;
    ptr++;
    snprintf(ptr->name, sizeof(ptr->name), "李四");
    ptr->score = 315.00;
    ptr++;
    snprintf(ptr->name, sizeof(ptr->name), "王五");
    ptr->score = 435.00;
    ptr++;
    // 重置指针到数组起始位置
    ptr = stu;
    float max_score = ptr->score;
    float sum_score = 0;
    struct info *max_stu = ptr;
    // 显示所有商品信息并找出价格最高的商品
    for (int i = 0; i < 3; i++)
    {
        if (max_score < ptr->score)
        {
            max_score = ptr->score;
            max_stu = ptr;
        }
        sum_score += ptr->score;
        ptr++;
    }
    float avg = sum_score / 3;
    printf("分数最高学员姓名为：%s,分数为：%.2f\n", max_stu->name, max_stu->score);
    printf("总分和为：%.2f,平均分为：%.2f\n", sum_score, avg);
    // 重置指针到数组起始位置
    ptr = stu;
    // 查询平均分以上学员的姓名
    printf("平均分以上学员的姓名为:");
    for (int i = 0; i < 3; i++)
    {
        if (avg < ptr->score)
        {
            printf("%s\t", ptr->name);
        }
        ptr++;
    }
    printf("\n");
    // 重置指针到数组起始位置
    ptr = stu;
    // （5）按照成绩排序
    for (int i = 0; i < 3 - 1; i++)
    {
        for (int j = 0; j < 3 - i - 1; j++)
        {
            if (stu[j].score < stu[j + 1].score)
            {
                // 交换成绩
                float temp_score = stu[j].score;
                stu[j].score = stu[j + 1].score;
                stu[j + 1].score = temp_score;
                // 交换姓名
                char temp_name[20];
                strcpy(temp_name, stu[j].name);
                strcpy(stu[j].name, stu[j + 1].name);
                strcpy(stu[j + 1].name, temp_name);
            }
        }
    }

    // 输出排序后的学员信息
    printf("按照成绩从高到低排序后的学员信息：\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%s的成绩为：%.2f\n", stu[i].name, stu[i].score);
    }

    free(stu);
}