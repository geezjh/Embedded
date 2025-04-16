#include "mysem.h"
#include <errno.h>

int mysem_exist(key_t key)
{
    if(-1 == semget(key,0,IPC_CREAT | IPC_EXCL) && errno == EEXIST)
         return   0;
    return -1;
}

int mysem_open(key_t key,int nsems) 
{
    return semget(key,nsems,IPC_CREAT|0600);
}

int mysem_p(int semid,int index)
{
    struct sembuf  ops[1]  = { index,  -1,  /*SEM_UNDO*/0 };  
    return  semop(semid,ops,1);
}
int mysem_v(int semid,int index)
{
    struct sembuf  ops[1]  = { index,  1,  /*SEM_UNDO*/0 };
    return semop(semid,ops,1);
}
int mysem_initvalue(int semid,int index,int value)
{
    union semun 
    {
        int  val;                               /* Value for SETVAL */
        struct semid_ds     *buf;              /*用于获取IPC_STAT, IPC_SET */
        unsigned short      *array;           /* Array for GETALL, SETALL */
        struct seminfo       *__buf;           /* Buffer for IPC_INFO  */
    }un;

    un.val = value;
    return semctl(semid,index,SETVAL,un);
}

int mysem_destroy(int semid)
{
    return semctl(semid,0,IPC_RMID);
}