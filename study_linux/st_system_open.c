#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>


int main(){
  //系统调用，创建文件的权限，先设置权限掩码为0
  umask(0);
  //库函数操作文件是通过文件流指针，但是系统调用是通过文件描述符进行文件的操作
  int fd = open("file.txt", O_RDONLY);//以只读的方式打开文件
  if(fd < 0){
    perror("open");
    //文件描述符小于0.打开文件失败
  }
  char buff[1024] ={'0'};
  int readsize = read(fd, buff, sizeof(buff));
  if(readsize < 0){
    //返回值为实际读到的字节数，如果读到的字节数小于指定的字节数，并不意味着失败，受文件中数字个数的影响，但如果小于0，则
    //一定出错，等于零的情况表示没有读到
    perror("read:");
  }
  printf("%s \n",buff);
  return 0;
}
