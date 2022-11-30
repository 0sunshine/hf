#pragma once

#include "OrderBase.h"
#include "../MediaGatewayLayout.h"

namespace hfsh
{

struct SetVolumeTerminal:public OrderRequest
{
    SetVolumeTerminal();

    int httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson,std::string& desc);

    int volume;
    std::vector<std::string> terminal_ids;
};

}
