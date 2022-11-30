#pragma once

#include "OrderBase.h"
#include "../MediaGatewayLayout.h"

namespace hfsh
{

struct SendProgram:public OrderRequest
{
    //这边需要用到这两个返回值
    struct Response
    {
        int code;
        std::string msg;

        REFLECT_WEBJSON_INPUT_ARGS_NUM(code,msg)
    };

    SendProgram();

    int setMediaGatewayWindow(const MediaGatewayWindow& window);

    //因为节目包上传必须携带终端id，往一个不存在终端id发送，以此当成是创建节目
    int httpSend(const OrderTarget& target,const std::string& token, Response& resJson,std::string& desc);

private:
    MediaGatewayWindow _window;
};

}
