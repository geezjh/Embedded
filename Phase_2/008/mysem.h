#ifndef __MYSEM_H
#define __MYSEM_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int mysem_exist(key_t);
int mysem_open(key_t,int);

int mysem_p(int,int);
int mysem_v(int,int);

int mysem_initvalue(int,int,int);
int mysem_destroy(int);



#endif