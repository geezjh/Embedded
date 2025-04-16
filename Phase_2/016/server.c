#include <stdio.h>
#include <arpa/inet.h>

typedef struct
{
    int request;
    char user[10];
    char pass[10];
} param_t;