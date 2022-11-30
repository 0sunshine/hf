#include "OrderBase.h"

#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/StringPartSource.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/StreamCopier.h>

#include <sstream>

#include "../mylog.h"

using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTMLForm;
using Poco::Net::FilePartSource;
using Poco::Net::StringPartSource;
using Poco::StreamCopier;

namespace hfsh
{

int OrderRequest::httpSend(const OrderTarget& target,const std::string &token, std::shared_ptr<cJSON> &resJson,std::string& desc)
try
{
    Poco::Net::HTTPClientSession httpClient(target.ip, target.port);
    Poco::Net::HTTPRequest req(HTTPRequest::HTTP_POST, "/API.aspx",HTTPRequest::HTTP_1_1);
    req.set("accept", "*/*");
    req.set("user-agent","EBS");
    req.set("Charset","UTF-8");
    req.set("Accept-Charset","UTF-8");
    req.setKeepAlive(true); //不知道为啥没生效

    HTMLForm req_form(HTMLForm::ENCODING_MULTIPART);

    req_form.add("token",token);
    req_form.add("service",this->_service);
    req_form.add("method",this->_method);

    for(auto& x: this->_textSources)
    {
        StringPartSource* p = new StringPartSource(x.second);
        req_form.addPart(x.first, p);
    }

    for(auto& x:this->_fileSources)
    {
        FilePartSource* p = new FilePartSource(x.second);
        req_form.addPart(x.first, p);
    }

    req_form.prepareSubmit(req,HTMLForm::OPT_USE_CONTENT_LENGTH);
    std::ostream& send = httpClient.sendRequest(req);
    req_form.write(send);

    HTTPResponse res;
    std::istream& body = httpClient.receiveResponse(res);

    std::ostringstream oss;
    StreamCopier::copyStream(body,oss);

    std::string recv_body = oss.str();

    cJSON* json = cJSON_Parse( recv_body.c_str() );

    if(json == nullptr)
    {
        TRACE_LOG_A(nullptr, TRACE_LOG_LEVEL_ERROR, "cJSON_Parse err : %s", recv_body.c_str())
    }

    resJson.reset(json,[](cJSON* p){ if(p!=nullptr) cJSON_Delete(p); });

    return static_cast<int>(res.getStatus());
}
catch (std::exception& e)
{
    desc = e.what();
    return -1;
}

}
