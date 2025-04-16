#include "slist.h"
#include "file.h"
#include "function.h"
#include "ui.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage  %s  datafile\n", argv[0]);
        return -1;
    }

    node_t *head = NULL;

    load(&head, argv[1]);

    welcome();

    while (mainmenu(&head, argv[1]))
        ;

    slist_destroy(&head);

    return 0;
}
