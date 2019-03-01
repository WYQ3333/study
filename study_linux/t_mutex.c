#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

int ticket = 100;
pthread_mutex_t mutex;

void* route(void* arg){
  char* id = (char*)arg;
  while(1){
    pthread_mutex_lock(&mutex);
    if(ticket > 1){
      usleep(1000);
      //在这个usleep相对于CPU较长的运行时间里，可能会将线程切换，因此当ticket>1时，会有别的线程进来，遇到sleep睡眠，此时如果别线程继续
      //进来，则在睡眠结束后两个线程均运行至注释这个地方，ticket-1之后，剩下的线程会继续-1，因此运行结果可能会出现-1的情况，所以，ticket--
      //应该是原子操作，当一个线程进行运行的时候，别的线程无法对ticket进行操作，这就需要线程的同步与互斥
      //互斥量，读写锁，条件变量等等实现同步与互斥的机制
      printf("%s sells ticket:%d \n", id, ticket);
      ticket--;
      pthread_mutex_unlock(&mutex);
    }
    else{
      pthread_mutex_unlock(&mutex);
      break;
    }
  }
}

int main(){
  pthread_t t1, t2, t3, t4;

  pthread_create(&t1, NULL, route, "thead 1");
  pthread_create(&t2, NULL, route, "thead 2");
  pthread_create(&t3, NULL, route, "thead 3");
  pthread_create(&t4, NULL, route, "thead 4");

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);
  
  return 0;
}

