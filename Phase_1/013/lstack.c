#include "lstack.h"
#include <stdlib.h>

int lstack_create(lstack_t *p, long sz)
{
   p->head = NULL;
   p->size = sz;
   p->top = -1;

   return 0;
}

int lstack_isfull(const lstack_t *p)
{
   return (p->top + 1 == p->size);
}
int lstack_isempty(const lstack_t *p)
{
   return (p->top == -1);
}

int lstack_push(lstack_t *p, data_t data)
{
   if (lstack_isfull(p))
      return -1;
   node_t *pnew = (node_t *)malloc(sizeof(node_t));
   if (pnew == NULL)
      return -1;

   pnew->data = data;
   pnew->next = p->head;
   p->head = pnew;
   p->top++;

   return 0;
}

int lstack_pop(lstack_t *p, data_t *data)
{
   if (lstack_isempty(p))
      return -1;

   node_t *q = p->head;
   *data = q->data;
   p->head = q->next;
   p->top--;
   free(q);
   return 0;
}

void lstack_free(lstack_t *p)
{
   while (p->head)
   {
      node_t *q = p->head;
      p->head = q->next;
      free(q);
   }
   p->size = 0;
   p->top = -1;
}
