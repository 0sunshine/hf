#pragma once

#include "OrderBase.h"
#include "../MediaGatewayLayout.h"

namespace hfsh
{

struct SendByProgramId:public OrderRequest
{
    SendByProgramId();

    int httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson,std::string& desc);

    std::vector<std::string> terminal_ids;
    std::string id; //½ÚÄ¿ID
};

}
