#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void * thread_run(void* arg){
  pthread_detach(pthread_self());
  printf("%s\n",(char*)arg);
  return NULL;
}


int mian(void){
  pthread_t tid;
  pthread_create(&tid, NULL, thread_run, NULL);
  if( pthread_create(&tid, NULL, thread_run, NULL ) != 0){
    printf("create thread error\n");
    return 1;
  }
  int ret = 0;
  sleep(1);
  if(pthread_join(tid, NULL) == 0){
    printf("pthread wait success\n");
    ret = 0;
  }
  else{
    printf("pthread wait failed\n");
    ret = 1;
  }
  return ret;
}
