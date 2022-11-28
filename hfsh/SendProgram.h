#pragma once

#include "OrderBase.h"
#include "../MediaGatewayLayout.h"

namespace hfsh
{

struct SendProgram:public OrderRequest
{
    SendProgram();

    int setMediaGatewayWindow(const MediaGatewayWindow& window);

    virtual int httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson,std::string& desc) override;

private:
    MediaGatewayWindow _window;
};

}
