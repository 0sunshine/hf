#pragma once

#include "OrderBase.h"
#include "../MediaGatewayLayout.h"

namespace hfsh
{

struct SendProgram:public OrderRequest
{
    //�����Ҫ�õ�����������ֵ
    struct Response
    {
        int code;
        std::string msg;

        REFLECT_WEBJSON_INPUT_ARGS_NUM(code,msg)
    };

    SendProgram();

    int setMediaGatewayWindow(const MediaGatewayWindow& window);

    //��Ϊ��Ŀ���ϴ�����Я���ն�id����һ���������ն�id���ͣ��Դ˵����Ǵ�����Ŀ
    int httpSend(const OrderTarget& target,const std::string& token, Response& resJson,std::string& desc);

private:
    MediaGatewayWindow _window;
};

}
