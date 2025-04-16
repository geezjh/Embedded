#ifndef __UI_H
#define __UI_H

#include "slist.h"

void welcome(void);
int mainmenu(node_t **, const char *);
int addmenu(node_t **, const char *);
int delmenu(node_t **, const char *);
int browsermenu(node_t *);

#endif
