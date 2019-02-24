#include<iostream>
#include<unistd.h>
#include<sys/types.h>

//ret返回值16273
//获取当前进程的pid16272
//获取当前进程的父进程的pid3556
//ret返回值0
//获取当前进程的pid16273
//获取当前进程的父进程的pid16272

//ret的返回值为子进程的进程id

int main(){
  int ret=fork();
  int pId=getpid();
  std::cout << "ret返回值" << ret << std::endl;
  std::cout << "获取当前进程的pid" << pId  << std::endl;
  int fpId=getppid();
  std::cout << "获取当前进程的父进程的pid" <<fpId  << std::endl;
  sleep(1);
  return 0;
}

