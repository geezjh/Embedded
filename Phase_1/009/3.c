// 定义一个表示公交线路的结构体，要求有线路名称，起始站，终点站，
// 里程等成员，定义结构体数组，用来存储4条公交线路信息，
// 并将数据保存到文件。要求验证是否存储成功。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char name[20];
    char start[20];
    char end[20];
    float mileage;
} Line;

int main()
{
    Line *lines = (Line *)malloc(4 * sizeof(Line));
    if (lines == NULL)
    {
        printf("内存分配失败\n");
        return 1;
    }
    strcpy(lines[0].name, "线路一");
    strcpy(lines[0].start, "A站");
    strcpy(lines[0].end, "B站");
    lines[0].mileage = 13.4;

    strcpy(lines[1].name, "线路二");
    strcpy(lines[1].start, "C站");
    strcpy(lines[1].end, "D站");
    lines[1].mileage = 21.3;

    strcpy(lines[2].name, "线路三");
    strcpy(lines[2].start, "E站");
    strcpy(lines[2].end, "F站");
    lines[2].mileage = 32.5;

    strcpy(lines[3].name, "线路四");
    strcpy(lines[3].start, "G站");
    strcpy(lines[3].end, "H站");
    lines[3].mileage = 42.6;

    FILE *fp;
    fp = fopen("1.txt", "w+");
    if (fp == NULL)
    {
        printf("文件打开失败\n");
        free(lines);
        return 1;
    }
    for (int i = 0; i < 4; i++)
    {
        fprintf(fp, "%s %s %s %.2f\n", lines[i].name, lines[i].start, lines[i].end, lines[i].mileage);
    }
    fclose(fp);
    return 0;
}