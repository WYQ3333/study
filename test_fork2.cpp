#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
using namespace std;
int main(){

  int ret = fork();

  //通常通过会对fork的返回值进行分流
  if(ret > 0){
    cout << "I am a father" << getpid() << endl;
  }else if(ret == 0){
    cout << "I am a child" << getpid() << endl;
  }else{
    perror("fork");
    //fork失败的原因：
    //1.当前进程所能创建的子进程数目达到上限
    //2.内存不够，文件描述符不够了，linux中一切皆文件
    return 1;
  }
  sleep(1);
  
  return 0;
}
