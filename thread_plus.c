#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<ctype.h>
#include<pthread.h>

#define MAX_THREAD  3  //线程个数

//初始化锁
static pthread_mutex_t    mutex = PTHREAD_MUTEX_INITIALIZER;

unsigned long long   main_counter,counter[MAX_THREAD]={0};

void* thread_worker(void*  arg)
{
    //先将void* 转为 int* 再赋值
    int  thread_num = *(int*)arg;
    //释放内存
    free((int*)arg);
    for(;;)
    {
        //加锁
        pthread_mutex_lock(&mutex);
        counter[thread_num]++;    //本线程的counter 加 1
        main_counter++;
        //解锁
        pthread_mutex_unlock(&mutex);
        //sleep(3);
    }
}

int main(int argc,char* argv[])
{
    int                 i,rtn,ch;
    pthread_t           pthread_id[MAX_THREAD] =  {0};  //存放线程

    int                 *param;
    for(i=0;i<MAX_THREAD;i++)
    { 
        //申请内存临时保存参数
        param = (int*)malloc(sizeof(int));
        *param = i;
        pthread_create(&pthread_id[i],NULL,thread_worker,param);
    }

    do
    {
        //加锁
        pthread_mutex_lock(&mutex);
        unsigned long long   sum = 0;
        for(i=0;i<MAX_THREAD;i++)
        {
            sum += counter[i];
            printf("No.%d: %llu\n",i,counter[i]);
        }
        printf("%llu/%llu\n",main_counter,sum);
        //解锁
        pthread_mutex_unlock(&mutex);
    }while((ch = getchar())!='q');

    //销毁锁资源
    pthread_mutex_destroy(&mutex);
    return 0;
}
