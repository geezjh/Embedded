#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage %s filepath\n", argv[0]);
        return -1;
    }
    for (int i = 1; i < argc; i++)
    {
        int fd = open(argv[i], O_RDONLY);
        if (-1 == fd)
        {
            perror("open");
            return -1;
        }
        printf("%s 文件打开成功\n", argv[i]);
    }
    return 0;
}