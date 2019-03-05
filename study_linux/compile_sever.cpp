#include"cpp-httplib/httplib.h"
#include"compile.hpp"
#include<jsoncpp/json/json.h>

int main(){
  //写在里面好，如果写在外面，起不到名字隔离的作用，提高了名字冲突的概率
  using namespace httplib;
  Server server;
  //Get注册了一个回调函数，这个函数的调用时机，处理Get方法的时候
  //lambda表达式：匿名函数，[](){};
  //get中的第一个参数是：路由
  server.Get("/compile",[](const Request& req, Response& resp){
      //根据具体的问题场景，根据请求，计算出响应结果
      (void)req;
      //如何从req中获取json请求，JSON如何和HTTP协议结合
      //JSON如何进行解析和构造？
      //
      //
      //在这里调用CompileAndRun
      Json::Value req_json;   //从req对象中获取到
      Json::Value resp_json;  //resp_json放到响应中
      Compiler::CompilerAndRun(req_json, &resp_json);
      //需要把Json对象序列化成字符串才能返回
      Json::FastWriter writer;
      resp.set_content(writer.write(resp_json),"text/plain");
      });
  server.listen("0.0.0.0",9092);       //传递端口号
  return 0;
}
