#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

pthread_cond_t cond;
pthread_mutex_t mutex;

void* r1(void* arg){
  while(1){
    pthread_cond_wait(&cond, &mutex);
    printf("活动\n");
  }
}

void* r2(void* arg){
  while(1){
    pthread_cond_signal(&cond);
    printf("唤醒条件变量\n");
    sleep(1);
  }
}

//注意：给条件变量加锁的原因是，条件变量应该是可以修改的值，因此要保证对条件变量的操作是一个原子操作，
//因此在pthread_cond_wait中的操作是，先给条件变量解锁（之前加过锁），然后休眠，被唤醒后非等待加锁
//为了保护条件的修改，所以我们使用互斥量保护，但是如果加锁之后，条件不满足而陷入休眠，则造成死锁，因此在
//休眠之前应该先解锁，但是解锁和休眠应该是源自操作，否则也会诱发死锁情况

int main(){
  pthread_t t1, t2;
  pthread_cond_init(&cond, NULL);
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&t1, NULL, r1, NULL);
  pthread_create(&t2, NULL, r2, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);

  return 0;
}
