#pragma once

#include "../CJson/cJSON.h"

#include <string>
#include <map>
#include <memory>
#include <stdint.h>

namespace hfsh
{

struct OrderTarget
{
    OrderTarget(const std::string& ip,uint16_t port ):ip(ip),port(port){}
    std::string ip;
    uint16_t port;
};

class OrderRequest
{
public:
    int httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson, std::string& desc);

protected:
    std::string _service;
    std::string _method;

    std::map<std::string,std::string> _textSources;
    std::map<std::string,std::string> _fileSources;
};

}

