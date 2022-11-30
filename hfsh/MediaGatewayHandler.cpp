#include "MediaGatewayHandler.h"

#include <Poco/Exception.h>

#include "../mylog.h"
#include "SendProgram.h"
#include "ListProgram.h"

hfsh::OrderTarget g_target {"192.168.22.120",9101};
std::string g_token = "123456";

namespace hfsh
{

static bool handleCreateProgram(const CreateProgramRequest& request, CreateProgramResponse& response)
{
    SendProgram order;
    order.setMediaGatewayWindow(request.window);

    std::shared_ptr<cJSON> resJson = nullptr;
    std::string desc;

    try
    {
        SendProgram::Response orderRes;
        int ret = order.httpSend(g_target, g_token, orderRes,desc);
        if(ret < 0)
        {
            response.code = ret;
            response.desc = desc;
            return true;
        }

        if(orderRes.code != 0)
        {
            response.code = orderRes.code;
            response.desc = orderRes.msg;
            return true;
        }

        //需要去节目列表根据节目名称反查节目ID号



    }
    catch (const Poco::Exception &e) {
        response.desc = e.displayText();
        TRACE_LOG_A(nullptr, TRACE_LOG_LEVEL_ERROR, "ex: %s", response.desc.c_str())
        return true;
    }
    catch (const std::exception &e) {
        response.desc = e.what();
        TRACE_LOG_A(nullptr, TRACE_LOG_LEVEL_ERROR, "ex: %s", response.desc.c_str())
        return true;
    }

    return true;
}

bool hander(const Protocol &input, Protocol &output)
{
    if(input.createProgramRequest.has_value())
    {
        CreateProgramResponse res;
        if( !handleCreateProgram(input.createProgramRequest.value(), res) )
        {
            TRACE_LOG_A(nullptr, TRACE_LOG_LEVEL_ERROR, "handleCreateProgram failed")
            return false;
        }

        output.createProgramResponse = res;
        return true;
    }

    return false;
}

}

