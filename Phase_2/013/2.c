/* 有一个水果盘，一次只能放一个水果，妈妈买苹果或者香蕉，
让儿子和女儿吃水果。儿子只吃苹果，女儿只吃香蕉。请设计代码实现这个过程。
提示：创建3个信号量，分别用于控制妈妈，儿子，女儿线程对果盘的访问，
妈妈线程先运行，当妈妈放置苹果时给儿子线程的信号量V操作，当放置香蕉时候给女儿线程的信号量V操作 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty;
sem_t apple;
sem_t banana;

void *mom(void *arg)
{
    for (int i = 0; i < 20; i++)
    {
        sem_wait(&empty);
        int choice = rand() % 2;
        if (choice == 0)
        {
            printf("妈妈放了一个苹果\n");
            sem_post(&apple);
        }
        else
        {
            printf("妈妈放了一个香蕉\n");
            sem_post(&banana);
        }
        sleep(1);
    }
    pthread_exit(NULL);
}

void *son(void *arg)
{
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&apple);
        printf("\t儿子吃了一个苹果\n");
        sem_post(&empty);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *daughter(void *arg)
{
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&banana);
        printf("\t女儿吃了一个香蕉\n");
        sem_post(&empty);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t mom_thread, son_thread, daughter_thread;

    sem_init(&empty, 0, 1);
    sem_init(&apple, 0, 0);
    sem_init(&banana, 0, 0);

    pthread_create(&mom_thread, NULL, mom, NULL);
    pthread_create(&son_thread, NULL, son, NULL);
    pthread_create(&daughter_thread, NULL, daughter, NULL);

    pthread_join(mom_thread, NULL);
    pthread_join(son_thread, NULL);
    pthread_join(daughter_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&apple);
    sem_destroy(&banana);
    return 0;
}