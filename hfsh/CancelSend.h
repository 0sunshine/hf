#pragma once

#include "OrderBase.h"
#include "../MediaGatewayLayout.h"

namespace hfsh
{

struct CancelSend:public OrderRequest
{
    CancelSend();

    int httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson,std::string& desc);

    std::string id;
};

}
