
#include <thread.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
//#include "thread_wrapper.h"
#if 0
struct task_wrapper_struct{
void *(*entry_point)(void*);
void *arg;
char *taskname;
};
#endif

static struct list_head task_list;

static int thread_init(struct thread_struct *task,char *name, int pri, int opts, int stksize,void *(*start_routine) (void *),void *arg);
/**
* DESCRIPTION
* the task_wrapper is the common thread start_route
*/
static void *task_wrapper( void *arg )
{
    struct thread_struct *task;
    void *(*entry_point)(void*);
    void *param;
    char * taskname;
    task = (struct thread_struct *)arg;
    
    
    entry_point = task->entry_point;
    param = task->arg;
    taskname = task->name;
    
    task->tid =  syscall(SYS_gettid);
    task->pid = getpid();
    /*set thread name to kernel*/
    prctl(PR_SET_NAME,taskname);
    
    entry_point(param);
    
    /*delete thread from thread_list*/
    thread_delete(task);
}

/**
*  DESCRIPTION
*
*  the thread_create function starts a new thread in the calling process.
*  the new thread starts execution by invoking start_routine();arg is 
*  passsed as the sole argument of start_routine().
*
*  RETURNS
*  on success,thread_create returns 0,on error it returns -1
*/
int thread_create(char *name, int pri, int opts, int stksize,void *(*start_routine) (void *), void *arg)
{

    int ret;
    struct thread_struct *task= NULL;
    task = malloc(sizeof(struct thread_struct)); 
        if( task == NULL)
        return ERROR;
    
    ret = thread_init(task, name, pri, opts, stksize, start_routine,arg);
        if (ret == OK) {
        thread_add(task);
        
        }else{
        printf("create thread failed\n");
        free(task);
        }
    
    return ret;
}

static int thread_init(struct thread_struct *task,char *name, int pri, int opts, int stksize,void *(*start_routine) (void *),void *arg)
{
    int ret=OK;
    int new_priority=0;
    int  sched_policy=0;
    int i; 
    struct sched_param  prv_priority;
    pthread_attr_t attr;
    pthread_t pthrid;
    
    if(NULL == start_routine || stksize<0)
        return ERROR;
    
    
    /*clear thread struct*/
    memset(task,0,sizeof(*task));
    
    if (name) {
        i = strlen(name) + 1;
        if(i> THREAD_NAME_SIZE)
        i = THREAD_NAME_SIZE;
        
        strncpy(task->name, name, i);
    
    }else{
        sprintf(task->name,"t%d",(int)task);
    } 
    
    task->pri = pri;
    task->entry_point = start_routine;
    task->arg = arg;
    
    if (pri > CONFIG_NORMAL_PRIORITY ){
        new_priority = 0;
        sched_policy = SCHED_OTHER; 
    }else{
        new_priority = pri;
        sched_policy = SCHED_FIFO;
    }
    
    pthread_attr_init(&attr);
    pthread_attr_getschedparam(&attr, &prv_priority);
    prv_priority.sched_priority = new_priority;
    
    pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED); 
    pthread_attr_setschedpolicy(&attr, sched_policy);
    pthread_attr_setschedparam(&attr, &prv_priority);
    
    ret = pthread_create(&pthrid, &attr,task_wrapper,task);
    if (ret != 0) {
        printf(" pthread_create returned error:");
        ret =ERROR;
    }
           
    return ret;
}


void thread_list_head_init(void)
{
    task_list.prev =NULL;
    task_list.next =NULL;
    pthread_mutex_init(&task_list.mtx,NULL);
}
void thread_add(struct thread_struct *task)
{
    struct thread_struct *p = NULL;
    struct thread_struct *q = NULL;
    pthread_mutex_lock(&task_list.mtx);
    p= task_list.next;
    
    if( p == NULL)
        task_list.next = task;
    else{ 
        while(p !=NULL){
            q= p;
            p=p->nxt_thread;
        }
    q->nxt_thread = task;
    }  
    pthread_mutex_unlock(&task_list.mtx);
}

void thread_delete(struct thread_struct *task)
{
    struct thread_struct *p =NULL;
    struct thread_struct *q=NULL;
    struct thread_struct *r=NULL;
    
    pthread_mutex_lock(&task_list.mtx); 
    p=task_list.next;
    
    printf("delete thread %s\n",task->name); 
    while(p!=NULL){
        q = p;
        p=p->nxt_thread;
        
        if(p !=NULL && p == task){
            r = p->nxt_thread;
            break;
        }
    }	  
    printf("p=%s\n",p->name);     
    q->nxt_thread = r;
    pthread_mutex_unlock(&task_list.mtx); 
    free(p);  

}

void show_all_thread(void)
{

    struct thread_struct *p;
    pthread_mutex_lock(&task_list.mtx);
    printf("pid tid name:\n");
    p= task_list.next;
	
    while(p !=NULL){
        printf("%d %d  %s\n",p->pid,p->tid,p->name);
        p=p->nxt_thread;
    }
    pthread_mutex_unlock(&task_list.mtx);
}
