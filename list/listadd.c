#include <list.h>
 
linklist* list_add(linklist* head)
{
    linklist * p = NULL;
    p = (linklist *)malloc(sizeof(linklist));
    if( p != NULL )
    {
        memset(p,0,sizeof(linklist));
        scanf("%d",&p->data);
        p->next = head;
    }
    head= p;
    return head;
}
