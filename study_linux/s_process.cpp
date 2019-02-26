#include<iostream>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
using namespace std;

void TestFunc(){
  int pid = fork();
  if(pid > 0){
    //父进程
    printf("I am father\n");
  }
  else if(pid == 0){
    printf("I am child\n");
  }
  else{
    perror("fork");
  }
}


int main(){
  TestFunc();
  return 0;
}
