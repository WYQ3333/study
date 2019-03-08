#pragma once
#include<unordered_map>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<stdint.h>
#include<sys/time.h>
#include<cstdlib>
//yum install boost-devel
#include<boost/algorithm/string.hpp>

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

//字符串切分：
//strtok();
//stringstream;
//boost split 函数(boost 是c++准标准库，备胎池)
class StringUtil{
  public:
    static void Split(const std::string& input, const std::string& split_char, std::vector<std::string>* output){
      boost::split(*output, input, boost::is_any_of(split_char), boost::token_compress_off);
    }
};

//url/body解析模块
class UrlUtil{
  public:
    static void ParseBody(const std::string& body, std::unordered_map<std::string, std::string>* params){
      //1.先对body字符串尽心切分，切分成键值对的形式，
      //   先按照&切分，再按照=号切分(通过boost 进行切分)
      std::vector<std::string> kvs;
      StringUtil::Split(body, "&", &kvs);
      for(size_t i = 0; i < kvs.size(); ++i){
        std::vector<std::string> kv;
        StringUtil::Split(kvs[i], "=", &kv);
        if(kv.size()!=2){
          continue;
        }
        //unorder_map[]操作的行为：如果key不存在，就新增，如果key存在，就获取到对应的value
        (*params)[kv[0]] = UrlDecode(kv[1]);
      }
      //2.对这里的键值对进行urldecode
    }
    static unsigned char ToHex(unsigned char x) 
    { 
      return  x > 9 ? x + 55 : x + 48; 
    }

    static unsigned char FromHex(unsigned char x) 
    { 
      unsigned char y;
      if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
      else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
      else if (x >= '0' && x <= '9') y = x - '0';
      else assert(0);
      return y;
    }

    static std::string UrlEncode(const std::string& str)
    {
      std::string strTemp = "";
      size_t length = str.length();
      for (size_t i = 0; i < length; i++)
      {
        if (isalnum((unsigned char)str[i]) || 
            (str[i] == '-') ||
            (str[i] == '_') || 
            (str[i] == '.') || 
            (str[i] == '~'))
          strTemp += str[i];
        else if (str[i] == ' ')
          strTemp += "+";
        else
        {
          strTemp += '%';
          strTemp += ToHex((unsigned char)str[i] >> 4);
          strTemp += ToHex((unsigned char)str[i] % 16);
        }
      }
      return strTemp;
    }

    static std::string UrlDecode(const std::string& str)
    {
      std::string strTemp = "";
      size_t length = str.length();
      for (size_t i = 0; i < length; i++)
      {
        if (str[i] == '+') strTemp += ' ';
        else if (str[i] == '%')
        {
          assert(i + 2 < length);
          unsigned char high = FromHex((unsigned char)str[++i]);
          unsigned char low = FromHex((unsigned char)str[++i]);
          strTemp += high*16 + low;
        }
        else strTemp += str[i];
      }
      return strTemp;
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
    
    //std::cout << content << std::endl;

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

