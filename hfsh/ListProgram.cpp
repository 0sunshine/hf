//
// Created by Administrator on 2022/11/24.
//

#include "ListProgram.h"


namespace hfsh {

ListProgram::ListProgram()
{
    _service = "program";
    _method = "list";
}

int ListProgram::httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson,std::string& desc)
{
    return OrderRequest::httpSend(target, token, resJson,desc);
}



}