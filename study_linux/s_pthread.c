#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void* thread1(void* arg){
  printf("thread1 returning \n");
  (void)arg;
  int *p = (int *)malloc(sizeof(int));
  *p = 1;
  return (void*)p;
}

void* thread2(void* arg){
  printf("thread2 returning \n");
  (void)arg;
  int *p = (int*)malloc(sizeof(int));
  *p = 2;
  pthread_exit((void *)p);
}

void* thread3(void* arg){
  (void)arg;
  while(1){
    printf("thread3 is returning\n");
    sleep(1);
  } 
  return NULL;
}

int main(){
  pthread_t tid;
  void* ret;
  //创建第一个线程
  //此线程并不关心线程的属性，因此将第二个参数置为NULL
  pthread_create(&tid, NULL, thread1, NULL);
  pthread_join(tid, &ret);
  //pthread_join(tid,&ret);函数的作用是：线程等待，因为线程结束之后不会释放所用的那部分虚拟地址空间，其他线程也不会复用，为了避免造成内存泄漏
  //需要等待线程的退出返回值，并且允许系统回收资源
  printf("thread return, thread id %X, return code: %d\n",tid, *(int*)ret);
  free(ret);

  //创建第二个线程
  pthread_create(&tid, NULL, thread2, NULL);
  pthread_join(tid, &ret);
  printf("thread return ,thread id %X, return code %d\n",tid ,*(int *)ret);

  //创建第三个线程
  pthread_create(&tid, NULL, thread3, NULL);
  sleep(3);
  pthread_cancel(tid);
  pthread_join(tid, &ret);
  if(ret == PTHREAD_CANCELED){
    printf("thread return, return id %X, return code PTHREAD_CANCELE\n", tid);
  }
  else{
    printf("thread return, return id %X, return code: NULL", tid);
  }
  return 0;
}

