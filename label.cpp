#pragma once 
#include<string.h>
#include<stdio.h>
#include<unistd.h>


void LabelTest(){
  char buf[102];    //将数组大小设置成102的原因是为例存放\0，防止访问越界
  memset(buf,0,sizeof(buf));
  const char* label = "|/-\\";
  int i = 0;
  const char* flag = "已完成";
  while( i < 101){
    printf("[%s][%d%%][%c][%s]\r",flag,i,label[i%4],buf);
    //回车的作用是使得光标再次回到首行，覆盖之前的打印结果，不加回车会使每行都打印，打印100行
    buf[i++] = '=';
    fflush(stdout);       //刷新缓冲区
    usleep(100000);
  }
  printf("\n");
}


int main(){
  LabelTest();
  return 0;
}
