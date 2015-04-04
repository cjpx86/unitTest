#ifndef THREAD_WRAPPER_H
#define THREAD_WRAPPER_H
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#define OK (0)
#define ERROR (-1)
#define THREAD_NAME_SIZE 32
#define CONFIG_NORMAL_PRIORITY 100
struct thread_struct{
    char name[THREAD_NAME_SIZE];
    pid_t tid;
    pid_t pid;
    int pri;
    struct thread_struct *nxt_thread;
    void *(*entry_point)(void*);
    void *arg;
};

struct list_head{
    pthread_mutex_t mtx;
    struct thread_struct *next;
    struct thread_struct *prev;
};	


extern	void thread_add(struct thread_struct *task);
extern void thread_delete(struct thread_struct *task);
extern void thread_list_head_init(void);
extern int thread_create(char *name, int pri, int opts, int stksize,void *(*start_routine) (void *), void *arg);
extern void show_all_thread(void);
#endif
