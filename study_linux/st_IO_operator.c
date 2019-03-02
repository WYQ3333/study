#include<stdio.h>
#include<string.h>


int main(){
  //以写的方式打开文件
  //文件存在则打开，文件并不存在则创建
  FILE* fd = fopen("myfile","w");
  printf("空指针sizeof:\n");
  char* str3 =NULL; 
  int temp3 = sizeof(str3);
  printf("%d \n", temp3); 
  printf("-------------\n"); 

  printf("hello：\n");
  char* str2 = "hello";
  int temp2 = sizeof(str2);
  printf("%d ", strlen(str2));
  printf("%d \n", temp2); 
  printf("-------------\n"); 

  printf("hello world sizeof&&strlen\n");
  char* str = "hello world\n";
  int temp = sizeof(str);
  printf("%d ", temp); 

  int cur = strlen(str);
  printf("%d \n", cur); //一次写sizeof(str)大小的数据，写一次

  int count = 5;
  while(count--){

  fwrite(str, strlen(str), 1, fd);
  }
  fclose(fd);
  return 0;
}
