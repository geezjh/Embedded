#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage %s filepath\n", argv[0]);
        return -1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (-1 == fd)
    {
        perror("open");
        return -1;
    }
    printf("%s 文件打开成功\n", argv[1]);

    int count[26] = {0};
    char buffer[1024];
    ssize_t b_read;
    while ((b_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        for (int i = 0; i < b_read; i++)
        {
            char c = tolower(buffer[i]);
            count[c - 'a']++;
        }
    }
    int max = 0;
    char a = ' ';
    for (int i = 0; i < 26; i++)
    {
        if (count[i] > max)
        {
            max = count[i];
            a = 'a' + i;
        }
    }
    printf("出现次数最多的字母是 %c，出现了 %d 次\n", a, max);
    close(fd);
    return 0;
}