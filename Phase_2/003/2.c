#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd = open("/dev/input/event2", O_RDONLY);
    if (fd == -1)
    {
        perror("open:");
        return -1;
    }

    struct input_event ev;
    while (1)
    {
        ssize_t bytes = read(fd, &ev, sizeof(struct input_event));
        if (bytes == sizeof(struct input_event))
        {
            if (ev.type == EV_ABS)
            {
                if (ev.code == ABS_X)
                {
                    printf("(x= %d)\n", ev.value);
                }
                else if (ev.code == ABS_Y)
                {
                    printf("(y= %d)\n", ev.value);
                }
            }
            else if (ev.type == EV_KEY && ev.code == BTN_LEFT && ev.value == 1)
            {
                break;
            }
        }
    }
    close(fd);
    return 0;
}