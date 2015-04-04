#ifndef LIST_H
#define LIST_H

#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
typedef struct taglist
{
	struct taglist * next;
	int data;
}linklist, *plinklist;

extern linklist* CreateListInHead();
extern void display(linklist * head);
extern void destory( linklist *head);
extern linklist* list_add(linklist* head);

#endif
