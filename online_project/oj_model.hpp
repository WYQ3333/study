#pragma once
#include<unordered_map>
#include<fstream>
#include"util.hpp"
#include<string>
#include<vector>
//MVC 经典的软件设计模式，20年前就有了 现在仍在使用，现代还有比如MVVM这个软件设计方式   
//M => model:负责存储数据
//V => view :负责显示界面
//C => controller:核心业务逻辑
//基于文件的方式完成题目的存储，具体组织方式：
//约定每个题目对应一个目录，目录的名字就是题目的id
//目录里包含以下几个文件：
//1)header.cpp    =>    代码矿建
//2)tail.cpp      =>    代码测试用例
//3)desc.txt      =>    题目的详细描述
//除此之外，再搞一个oj_config.cfg文件，作为一个总的入口文件，这个文件是一个行文本文件
//这一行里面包含以下几个信息：题目的id，题目的名字，题目的难度，题目对应的目录
//model要做的事情就是把我们做的配置文件中的题目信息加载起来，供服务其随时使用


struct Question{
  std::string id;
  std::string name;
  std::string dir;        //表示题目对应的目录,目录中包含了题目描述，题目的代码框架，题目的测试用例
  
  std::string star;       //表示题目等级
  std::string desc;       //题目的描述
  std::string header_cpp; //题目的代码框架中的代码
  std::string tail_cpp;   //题目的测试用例代码
};

class OjModel{
  private:
    std::unordered_map<std::string, Question> model_;
  public:

    //把文件上的数据加载起来
    bool Load(){
      std::ifstream file("./oj_data/oj_config.cfg");
      if(!file.is_open()){
        return false;
      }
      std::string line;
      while(std::getline(file,line)){
        std::vector<std::string> tokens;
        StringUtil::Split(line, "\t", &tokens);
        if(tokens.size() != 4 ){
          LOG(ERROR) << "config file format error!\n";
          continue;
        }
        Question q;
        q.id = tokens[0];
        q.name = tokens[1];
        q.star = tokens[2];
        q.dir = tokens[3];
        FileUtil::Read(q.dir + "/desc.txt", &q.desc);
        FileUtil::Read(q.dir + "/header.cpp", &q.header_cpp);
        FileUtil::Read(q.dir + "/tail.cpp", &q.tail_cpp);
        model_[q.id] = q;
      }
      file.close();
      LOG(INFO) << "Load" << model_.size() << "questions\n";
      return true;
    }

    bool GetAllQuestions(std::vector<Question>* questions)const{
      questions->clear();
      for(const auto& kv:model_){
	questions->push_back(kv.second); 
      }
      return true;
    }

    bool GetQuestion(const std::string& id, Question* q)const{
      auto pos = model_.find(id);
      if(pos == model_.end()){
	      return false;
      }
      *q = pos->second;
      return true;
    }
};
