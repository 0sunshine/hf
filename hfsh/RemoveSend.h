#pragma once

#include "OrderBase.h"
#include "../MediaGatewayLayout.h"

namespace hfsh
{

struct RemoveSend:public OrderRequest
{
    RemoveSend();

    int httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson,std::string& desc);

    std::string id;
};

}
