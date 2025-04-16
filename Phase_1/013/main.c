#include "lstack.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    lstack_t s;

    lstack_create(&s, 10);

    for (register int i = 0; i < 15; i++)
    {
        if (-1 == lstack_push(&s, i + 1))
        {
            fprintf(stderr, "stack is full %d\n", i);
            break;
        }
    }

    while (!lstack_isempty(&s))
    {
        data_t data;
        if (lstack_pop(&s, &data) == 0)
            printf("%3d", data);
    }
    printf("\n");

    lstack_free(&s);
    return 0;
}
