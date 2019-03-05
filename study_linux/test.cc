#include"compile.hpp"
#include"util.hpp"
#include<jsoncpp/json/json.h>

int main(){
  Json::Value req;
  req["code"] = "#include<stdio.h>\n int main() {printf(\"heheh\");return 0;}";
  req["stdin"] = "";
  Json::Value resp;
  Compiler::CompilerAndRun(req, &resp);
  Json::FastWriter writer;
  LOG(INFO) << writer.write(resp) << std::endl;
  return 0;
}
