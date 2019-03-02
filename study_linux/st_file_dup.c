#include<stdio.h>
#include<string.h>
#include<errno.h>

int main(){
  FILE* fd = fopen("file.txt", "r");
  if(NULL == fd){
    perror("fopen:");
    //打开文件失败
  }
  char buf[1024];
  memset(buf, '0', 1024);
  fread(buf, 1024, 1, fd);
  printf("%s\n", buf);
  //将buf 中的数据输出到标准输出上
  fprintf(stdout, buf);
  return 0;
}
