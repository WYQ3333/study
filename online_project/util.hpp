#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<stdint.h>
#include<sys/time.h>
#include<cstdlib>

//1.获取一个时间戳工具

class TimeUtil{
public:
  //获取当前时间的时间戳,time函数只能获取到秒级时间戳，无法获取毫秒级
  static int64_t TimeStamp(){
    struct timeval tv;
    //此结构体的头文件是cstdlib
    ::gettimeofday(&tv,NULL);
    return tv.tv_sec;
  }

  static int64_t TimeStampMS(){
    struct timeval tv;
    ::gettimeofday(&tv,NULL);
    //获取到的毫秒级时间戳
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
  }
};

//2.打印日志的工具
//期望打印出的日志格式为：
//[I1550892581 util.hpp:31] hello    [时间戳，文件名：行号 内容]
//日志的使用方式形如：
//LOG(INFO) << "hello" << "\n";
//日志的级别：
//FATAL:致命的
//ERROR:错误
//WARNING:警告
//INFO:提示
enum Level{
  INFO,
  WARNING,
  ERROR,
  FATAL,
};

//将输出日志的格式设置完成
inline std::ostream& Log(Level level, const std::string& file_name, int line_num){
  std::string prefix = "[";
  if(level == INFO){
    prefix += "I";
  }else if (level == WARNING){
    prefix += "W";
  }else if (level == ERROR){
    prefix += "E";
  }else if (level == FATAL){
    prefix += "F";
  }
  prefix += std::to_string(TimeUtil::TimeStamp());
  prefix += " ";
  prefix += file_name;
  prefix += ":";
  prefix += std::to_string(line_num);
  prefix += "] ";
  std::cout << prefix;
  return std::cout;
}

#define LOG(level) Log(level, __FILE__, __LINE__)
//到此日志文件准备好


//3.准备一个文件相关工具类
class FileUtil{
public:
  //传入一个文件路劲，帮我们把文件的所有内容都读出来放到content字符串中
  static bool Read(const std::string& file_path, std::string* content){
    content->clear();         //将原来字符串中的内容清零
    std::ifstream file(file_path.c_str());
    if(!file.is_open()){
      return false;
    }
    std::string line;
    while(std::getline(file,line)){
      *content += line + "\n";
    }

    //一个进程最多可以打开几个文件，回答具体数字就是错误的答案，
    //因为可以修改
    //ulimit -a
    //ulimit -n 1024 将打开文件的最大值改为1024
    //因此说可配置
    
    file.close();
    return true;
  }

  static bool Write(const std::string& file_path, const std::string& content){
    std::ofstream file(file_path.c_str());
    if(!file.is_open()){
      return false;
    }
    file.write(content.c_str(), content.size());
    file.close();
    return true;
  }
};

