/**
* this file is implementation the test case for stack overflower
* author: Alex.Li
**/

#include<thread.h>

static void test_func3(char *arg)
{
    int j=0;
    int i=1;
    
    printf("%s[%d]\n",__FUNCTION__,__LINE__);
}
void test_func2(int x,int y)
{
    char buf[100];
    printf("test func 2 %d\n",x+y);
    test_func3(NULL);
    memset(buf,0,1024);
    printf("test func 2 end\n");
}
void test_func(void)
{
    int i=5;
    int j=6;
    printf("test func\n");
    test_func2(3,5);

    i++;
    j++;
    printf("%d %d\n",i,j);
}
void * stackOverFlower(void *arg)
{
    printf("stack overflower test run\n");
    test_func();
    return NULL;
}

int main()
{
    thread_list_head_init();
    thread_create("stackOverFlower",70,0,0,stackOverFlower,NULL);
    show_all_thread();

    while(1)
        sleep(100);

return 0;
}
