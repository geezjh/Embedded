// 设计一个结构体，存放一个学员信息并显示，存放两个学员信息，算他们的平均分。
#include <stdio.h>
#include <string.h>
struct info
{
    int no;
    char name[20];
    int age;
    char sex[20];
    float score;
} stu1 = {1, "张三", 18, "男", 230.00};

int main()
{
    struct info stu2;
    stu2.no = 2;
    strcpy(stu2.name, "李四");
    stu2.age = 20;
    strcpy(stu2.sex, "女");
    stu2.score = 300;
    printf("%s的学号为：%d,年龄为：%d,性别为：%s,成绩为：%.2f\n", stu1.name, stu1.no, stu1.age, stu1.sex, stu1.score);
    printf("%s和%s的平均分为：%.2f\n", stu1.name, stu2.name, (stu1.score + stu2.score) / 2);
    return 0;
}
