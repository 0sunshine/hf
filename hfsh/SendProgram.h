#pragma once

#include "OrderBase.h"
#include "../MediaGatewayLayout.h"

namespace hfsh
{

struct SendProgram:public OrderRequest
{
    struct Response
    {

    };

    SendProgram();

    int setMediaGatewayWindow(const MediaGatewayWindow& window);

    int httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson,std::string& desc);

private:
    MediaGatewayWindow _window;
};

}
