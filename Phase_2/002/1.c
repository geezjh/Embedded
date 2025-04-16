#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#define LEN (800 * 480 * 4)
int main(int argc, char **argv)
{
    int lcdfd = open("/dev/fb0", O_RDWR);
    if (lcdfd == -1)
    {
        perror("open:");
        return -1;
    }

    uint32_t *p = (uint32_t *)mmap(NULL, LEN, PROT_WRITE | PROT_READ, MAP_SHARED, lcdfd, 0);
    if (p == MAP_FAILED)
    {
        perror("mmap");
        close(lcdfd);
        return -1;
    }
    for (int i = 0; i < 800; i++)
    {
        for (int j = 0; j < 480; j++)
        {
            if (j >= 0 && j <= 160)
                p[i + 800 * j] = 0x00ff0000;
            else if (j >= 161 && j <= 320)
                p[i + 800 * j] = 0x00ffffff;
            else
                p[i + 800 * j] = 0x000000ff;
        }
    }
    munmap(p, LEN);
    close(lcdfd);
    return 0;
}
