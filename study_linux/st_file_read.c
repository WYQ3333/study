#include<stdio.h>
#include<string.h>
#include<errno.h>

int main(){
  FILE* fd = fopen("file.txt", "r");
  if(NULL == fd){
    perror("fopen");
  }
  //新建一个缓冲区，将读到的数据存放到缓冲区中
  char* buf[1024];
  memset(buf, '0', 1024);
  //从fd文件描述符所在的位置读，一次读一个读1024次
  fread(buf, 1, 1024, fd);
  printf("%s", buf);
  printf("\n");
  fclose(fd);
  return 0;
}
