/* 编程模拟4个售票窗口共同出售 100 张票务的功能，要求每个窗口不能卖出同一张票，实现售票过程
提示：创建4个线程用于模拟售票窗口，用一个全局变量来模拟100张票，4个线程
共同访问这个数据，让该数据减一，为0时4个线程一起结束*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int ticket_num = 100;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *sell_ticket(void *arg)
{
    int window = *(int *)arg + 1;
    free(arg);

    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (ticket_num > 0)
        {
            printf("窗口%d 卖出第%d张票\n", window, ticket_num--);
            pthread_mutex_unlock(&mutex);
            usleep(1000);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    printf("窗口%d 停止售票\n", window);
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t windows[4];

    for (int i = 0; i < 4; i++)
    {
        int *arg = (int *)malloc(sizeof(int));
        *arg = i;
        pthread_create(&windows[i], NULL, sell_ticket, arg);
    }

    for (int i = 0; i < 4; i++)
    {
        pthread_join(windows[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    printf("所有票已售罄\n");
    return 0;
}