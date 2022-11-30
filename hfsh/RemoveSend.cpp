//
// Created by Administrator on 2022/11/24.
//

#include "RemoveSend.h"


namespace hfsh {

RemoveSend::RemoveSend()
{
    _service = "send";
    _method = "remove";
}

int RemoveSend::httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson,std::string& desc)
{
    _textSources["id"] = id;
    return OrderRequest::httpSend(target, token, resJson,desc);
}


}