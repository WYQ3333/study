#include<unistd.h>
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;


int main(){
  char buf[102];
  memset(buf,0,sizeof(buf));
  const char* label="|/-\\";
  int i = 0;
  while(i < 100){
    printf("[%s],[%d%%],[%c]\r",buf,i,label[i%4]);
    fflush(stdout);
    buf[i++]='=';
    //睡眠，调整一下
    sleep(1);
  }
  printf("\n");
  return 0;
}


