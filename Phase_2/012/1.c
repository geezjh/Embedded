/* 创建3个线程，3个线程中的其中两个线程分别实现对
共享数据的读，写访问，第3个线程在运行5S中后，向其中
的某一个线程发送取消请求后退出，要求被取消的线程退出后，另一个线程能正常运行。
提示: 如果向让另一个线程能正常运行，则被取消的线程必须要能够释放 mutex  */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int shared_data = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t writer_tid, reader_tid;

void clean_handler(void *arg)
{
    pthread_mutex_unlock((pthread_mutex_t *)arg);
    printf("取消线程释放了互斥锁\n");
}

void *writer(void *arg)
{
    pthread_cleanup_push(clean_handler, &mutex);

    while (1)
    {
        pthread_mutex_lock(&mutex);
        shared_data++;
        printf("Writer: updated data to %d\n", shared_data);
        pthread_mutex_unlock(&mutex);
        sleep(1);
        pthread_testcancel();
    }

    pthread_cleanup_pop(1);
    return NULL;
}

void *reader(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("Reader:current data is %d\n", shared_data);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void *controller(void *arg)
{
    sleep(5);
    printf("Controller:canceling writer thread\n");
    pthread_cancel(writer_tid);
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_create(&writer_tid, NULL, writer, 0);
    pthread_create(&reader_tid, NULL, reader, 0);
    pthread_t controller_tid;
    pthread_create(&controller_tid, NULL, controller, 0);

    pthread_join(writer_tid, NULL);
    pthread_join(controller_tid, NULL);
    pthread_join(reader_tid, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}