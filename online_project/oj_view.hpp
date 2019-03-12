#pragma once 
#include<ctemplate/template.h>
#include"oj_model.hpp"
class OjView{
   public:
      static void RenderAllQuestion(const std::vector<Question>& all_questions, std::string* html){
        ctemplate::TemplateDictionary dict("all_questions");
        for(const auto& question:all_questions){
	    ctemplate::TemplateDictionary* table_dict = dict.AddSectionDictionary("question");
	    table_dict->SetValue("id",question.id);
	    table_dict->SetValue("name",question.name);
	    table_dict->SetValue("star",question.star);
	}
	ctemplate::Template* tp1;
	tp1 = ctemplate::Template::GetTemplate("./template/all_questions.html", ctemplate::DO_NOT_STRIP);
	tp1->Expand(html, &dict);
      }
};
