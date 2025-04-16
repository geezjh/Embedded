#include <stdio.h>
#include <ctype.h>

int main() {
    char a;
    printf("请输入字母：");
    scanf("%c", &a); 
    printf("大写字母转换为小写字母：%c\n", a + 32);
}
