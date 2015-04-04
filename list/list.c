#include <list.h>

 linklist* CreateListInHead()
{
 linklist *L = NULL;
 linklist *tmp = NULL;
 int data = 0;
 int i = 0;
 int NodeCount = 0;
 if(NULL != L)
 {
  free(L);
 }
 printf("Please input the count that you want:\n");
 scanf("%d",&NodeCount);
 if(NodeCount <= 0)
 {
  printf("Create fail!\n");
  return L;
 }
 printf("Please input the last Data:\n");
 scanf("%d",&data);
 L = (linklist *)malloc(sizeof(linklist));
 if(NULL != L)
 {
  memset(L,0,sizeof(linklist));
 }
 else
 {
  printf("Create List malloc fail!\n");
  return (L = NULL);
 }
 L->data = data;
 L->next = NULL;
 //head = L;
 while(-- NodeCount)
 {
  printf("input the data %d:\n",NodeCount);
  data = 0;
  scanf("%d",&data);
  tmp = (linklist *)malloc(sizeof(linklist));
  if(NULL != tmp)
  {
   memset(tmp,0,sizeof(linklist));
  }
  else
  {
   printf("Create List malloc fail!\n");
   return (tmp = NULL);
  }
  tmp->data = data;
  tmp->next = L;
  L = tmp;  
 }
 return L;
}


 void display(linklist * head)
	{
		linklist * p = head;
		while( p!= NULL)
		{
			printf("%d  ",p->data);
			p = p->next;
		}
		printf("\n");
}

 void destory( linklist *head)
{
	while(head != NULL)
	{
		 linklist * p = head;
		head = head->next;
		free(p);
	}
}
