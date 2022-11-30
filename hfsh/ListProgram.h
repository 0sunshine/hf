#pragma once

#include "OrderBase.h"
#include "../MediaGatewayLayout.h"

namespace hfsh
{

struct ListProgram:public OrderRequest
{
    struct Response
    {
        int code;
        std::string msg;

        REFLECT_WEBJSON_INPUT_ARGS_NUM(code,msg)
    };

    ListProgram();

    int httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson,std::string& desc);

};

}
