#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define CONSUMERS_COUNT 2
#define PRODUCERS_COUNT 2

struct msg{
  struct msg *next;
  int num;
};

struct msg *head = NULL;

pthread_cond_t cond;
pthread_mutex_t mutex;
//创建线程池
pthread_t threads[CONSUMERS_COUNT + PRODUCERS_COUNT];

void* consumers(void* arg){
  int num = *(int*)arg;
  free(arg);
  struct msg *mp;
  for( ; ; ){
    pthread_mutex_lock(&mutex);
    //加锁，保证线程安全
    while( head == NULL ){
      printf("%d begin wait a condition...\n", num);
      pthread_cond_wait(&cond, &mutex);
    }
    printf("%d end wait a condition...\n", num);
    printf("%d begin consume product...\n", num);
    mp = head;
    //消费者从队列中取走一个产品
    head = mp->next;
    pthread_mutex_unlock(&mutex);
    printf("consume %d\n",mp->num);
    free(mp);
    printf("%d end consume product ...\n", num);
    sleep(rand()%5);
  }
}

void* producers(void* arg){
  struct msg *mp;
  int num = *(int*)arg;
  free(arg);
  for(; ;){
    printf("%d begin produce product...\n", num);
    mp = (struct msg*)malloc(sizeof(struct msg));
    mp->num = rand()%1000 + 1;
    printf("producer %d\n", mp->num);
    pthread_mutex_lock(&mutex);
    mp->next = head;
    head = mp;
    //队列中已经生产好了数据,通知消费者可以来购买了
    printf("%d end produce product ...\n", num);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    sleep(rand()%5);
  }
}

int main(){
  //产生随机数
  srand(time(NULL));

  //初始化条件变量与互斥量
  pthread_cond_init(&cond, NULL);
  pthread_mutex_init(&mutex, NULL);

  int i = 0;
  for(i = 0; i < CONSUMERS_COUNT; ++i){
    int *p = (int *)malloc(sizeof(int));
    *p = i;
    pthread_create(&threads[i], NULL, consumers, (void*)p);
  }

  for(i = 0;i < PRODUCERS_COUNT; ++i){
    int *p = (int*)malloc(sizeof(int));
    *p = i;
    pthread_create(&threads[CONSUMERS_COUNT+i], NULL, producers, (void*)p);
  }
  for(i = 0; i <  CONSUMERS_COUNT + PRODUCERS_COUNT; ++i){
    pthread_join(threads[i], NULL);
  }

  //销毁互斥量与条件变量
  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&mutex);
  return 0;
}
