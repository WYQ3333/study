#include"cpp-httplib/httplib.h"
#include"util.hpp"
#include"oj_model.hpp"
#include"oj_view.hpp"

int main(){
   OjModel model;
   model.Load();
   using namespace httplib;
   Server server;
   server.Get("/all_questions",[&model](const Request& req, Response& resp){
      (void)req;
      std::vector<Question> all_questions;
      model.GetAllQuestions(&all_questions);
      std::string html;
      OjView::RenderAllQuestion(all_questions, &html);
      resp.set_content(html, "text/html");
   });
   server.Get("/question",[&model](const Request& req, Response& resp){
   });
   server.set_base_dir("./wwwroot");
   server.listen("0.0.0.0",9092);
   return 0;
}
