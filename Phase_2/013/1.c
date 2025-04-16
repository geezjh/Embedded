/* 有四个线程1、2、3、4。线程1的功能就是输出1，线程2的功能就是输出2，
以此类推.........  现要让四个线程输出呈如下格式中的任一种：
A：1 2 3 4 1 2....
B：2 3 4 1 2 3....
C：3 4 1 2 3 4....
D：4 1 2 3 4 1....
请设计程序 (四个线程按顺序输出5次就可以)。
提示：  1. 使用条件变量，
        2. 定义一个数组表示线程编号  a[] = {0,1,2,3}创建线程同时传递线程编号，
        3. 定义一个全局变量代表某个线程的编号，在线程中判断当全局变量的取值和
        传递的线程编号相同时， 输出对应的数据(1,2,3,4),否则用条件变量阻塞线程，
        能运行的线程输出数据后，修改全局变量，并对其他被条件变量阻塞的线程通知， */
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define NUM_LOOPS 5

pthread_mutex_t mutex;
pthread_cond_t cond;

int current_thread = 0;

void *printf_number(void *arg)
{
        int thread_id = *(int *)arg;
        for (int i = 0; i < NUM_LOOPS; i++)
        {
                pthread_mutex_lock(&mutex);
                while (current_thread != thread_id)
                {
                        pthread_cond_wait(&cond, &mutex);
                }
                printf("%d ", thread_id + 1);
                current_thread = (current_thread + 1) % NUM_THREADS;

                pthread_cond_broadcast(&cond);
                pthread_mutex_unlock(&mutex);
        }
        pthread_exit(NULL);
}

int main(int argc, char **argv)
{
        pthread_t threads[NUM_THREADS];
        int thread_ids[NUM_THREADS] = {0, 1, 2, 3};

        pthread_cond_init(&cond, NULL);
        pthread_mutex_init(&mutex, NULL);

        for (int i = 0; i < NUM_THREADS; i++)
        {
                pthread_create(&threads[i], NULL, printf_number, &thread_ids[i]);
        }

        for (int i = 0; i < NUM_THREADS; i++)
        {
                pthread_join(threads[i], NULL);
        }

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        printf("\n");
        return 0;
}