//
// Created by Administrator on 2022/11/24.
//

#include "SendByProgramId.h"
#include "../CJson/json_reflection_utility.h"

namespace hfsh {

SendByProgramId::SendByProgramId()
{
    _service = "send";
    _method = "sendByProgramId";
}

struct RequestData
{
    std::string beginDate;
    std::string endDate;
    std::string beginTime;
    std::string endTime;
    std::vector<int> weeks;
    std::vector<std::string> terminalIds;
    std::string programId;
    int priority;

    REFLECT_WEBJSON_OUTPUT_ARGS_NUM(beginDate,endDate,beginTime,endTime,weeks,
            terminalIds,programId,priority)
};

int SendByProgramId::httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson,std::string& desc)
{
    RequestData requestData;
    requestData.beginDate = "2000-01-11";
    requestData.endDate = "2100-01-12";
    requestData.beginTime = "00:11:11";
    requestData.endTime = "22:11:12";
    requestData.weeks = std::vector<int>{1,2,3,4,5,6,0};
    requestData.priority = 1;

    requestData.programId = id;
    requestData.terminalIds = terminal_ids;

    //创建program.json
    cJSON* requestDataJson = requestData.genarateWebJsonOutput();
    if(requestDataJson == nullptr)
    {
        desc = "生成requestDataJson失败";
        return -1;
    }

    std::string json_text = JsonHandler::JsonToString(requestDataJson);
    cJSON_Delete(requestDataJson);

    _textSources["data"] = json_text;

    return OrderRequest::httpSend(target, token, resJson,desc);
}



}