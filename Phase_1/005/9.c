#include <stdio.h>

int main() {
    char s1[5] = "abcd"; 
    char s2[5] = "abce"; // 同上
    int i = 0; // 初始化索引 i

    while (s1[i] != '\0' && s2[i] != '\0') { // 比较直到遇到字符串结尾 '\0'
        if (s1[i] > s2[i]) {
            printf("s1 > s2\n");
            return 1; // s1 大于 s2，返回1
        } else if (s1[i] < s2[i]) {
            printf("s2 > s1\n");
            return -1; // s2 大于 s1，返回-1
        }
        i++; // 增加索引，比较下一个字符
    }

    // 如果两个字符串的长度不同，但前面的部分都相同，则较长的字符串大于较短的
    if (s1[i] != '\0') {
        printf("s1 > s2\n");
        return 1;
    } else if (s2[i] != '\0') {
        printf("s2 > s1\n");
        return -1;
    } else {
        printf("s1 == s2\n"); // 如果两个字符串完全相同，返回0
        return 0;
    }
}
