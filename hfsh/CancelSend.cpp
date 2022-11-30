//
// Created by Administrator on 2022/11/24.
//

#include "CancelSend.h"


namespace hfsh {


CancelSend::CancelSend()
{
    _service = "send";
    _method = "cancel";
}

int CancelSend::httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson,std::string& desc)
{
    _textSources["id"] = id;
    return OrderRequest::httpSend(target, token, resJson,desc);
}

}