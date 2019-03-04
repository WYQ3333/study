#include<stdio.h>
#include<signal.h>
#include<unistd.h>

//这段程序的功能：
//定义了两个信号集
//一个信号集用来将SIGINT信号添加的阻塞信号集
//即将ctrl+c阻塞，当按下该命令之后，无法终止程序，ctrl+\同样也可以终止程序
//另一个信号集用来初始化未决信号集，当按了ctrl+c之后，由于该信号被阻塞了
//因此可以在未决信号集中找到SIGINT信号
//用sigismember(&set)来判断SIGINT是否在未决信号集中
void printsingal(sigset_t *temp){
  size_t i = 0;
  for(i = 0; i < 32; ++i){
    //sigmemeber若包含，则返回1，不包含则返回0；失败返回-1
    if(sigismember(temp, i)){
      usleep(10000);
      putchar('1');
    }
    else{
      usleep(10000);
      putchar('0');
    }
  }
  printf("\n");
}

int main(){

  //定义普通信号集
  sigset_t s,p;
  //初始化s信号集，使其中所有信号的比特位都清零
  //表示信号集不包含任何有效信号
  sigemptyset(&s);
  sigemptyset(&p);
  //向s信号集中添加2号信号SIGINT
  sigaddset(&s, SIGINT);
  //如果第三个参数非空，则读取当前信号屏蔽字，由第三个参数传出
  //如果第二个参数非空，表明将第二个参数所指向的信号集以第一个参数的方式
  //添加到阻塞信号集
  sigprocmask(SIG_BLOCK, &s, NULL);

  while(1){
    //将信号集添加到未决信号集（未决信号表示注册之后，递达之前信号所处的状态）
    sigpending(&p);
    printsingal(&p);
  }
  return 0;
}
