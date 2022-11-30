#include <iostream>

#include "hfsh/SendProgram.h"
#include "hfsh/ListProgram.h"
#include "hfsh/CancelSend.h"
#include "hfsh/RemoveSend.h"

#include "MediaGatewayLayout.h"
#include "hfsh/SendByProgramId.h"
#include "hfsh/SetVolumeTerminal.h"

const hfsh::OrderTarget target {"192.168.22.120",9101};
const std::string& token = "123456";

int testSendProgram()
{
    MediaGatewayWindow window;
    window.program_id = u8"测试节目";
    window.width = 1920;
    window.height = 1080;

    MediaGatewayImage image1;
    image1.width = 200;
    image1.height = 200;
    image1.x = 0;
    image1.y = 0;
    image1.files.push_back(u8"d:/福利xxxx.jpg");
    image1.files.push_back(u8"C:/Users/Administrator/Downloads/关注FancyPig公众号.png");

    window.images.push_back(image1);

//    MediaGatewayVideo video2;
//    video2.width = 200;
//    video2.height = 200;
//    video2.x = 200;
//    video2.y = 0;
//    video2.files.push_back(u8"e:/习近平百年庆典讲话01.mp4");
//    window.videos.push_back(video2);

    MediaGatewayAudio audio3;
    audio3.files.push_back(u8"e:/感谢你曾来过.mp3");
    window.audios.push_back(audio3);

    MediaGatewayText text4;
    text4.width = 400;
    text4.height = 200;
    text4.x = 0;
    text4.y = 200;

    text4.color = "#00ff00";
    text4.fontSize = 40;
    text4.direction = MediaGatewayText::Right;
    text4.speed = 2;

    text4.text = "asdasdasdasdasdasd";
    window.texts.push_back(text4);

    hfsh::SendProgram order;
    order.setMediaGatewayWindow(window);

    std::shared_ptr<cJSON> resJson = nullptr;
    std::string desc;

    int http_status = order.httpSend(target, token, resJson,desc);

    if(http_status < 0)
    {
        std::cout << desc << "   " << http_status << std::endl;
        return -1;
    }

    std::cout << "http return " << http_status << std::endl;

    if(resJson)
    {
        std::cout << cJSON_Print(resJson.get()) << std::endl;
    }

    return 0;
}

int testListProgram()
{
    hfsh::ListProgram order;
    std::shared_ptr<cJSON> resJson = nullptr;
    std::string desc;

    int http_status = order.httpSend(target, token, resJson,desc);

    if(http_status < 0)
    {
        std::cout << desc << "   " << http_status << std::endl;
        return -1;
    }

    std::cout << "http return " << http_status << std::endl;

    if(resJson)
    {
        std::cout << cJSON_Print(resJson.get()) << std::endl;
    }

    return 0;
}

int testCancelSend()
{
    hfsh::CancelSend order;
    std::shared_ptr<cJSON> resJson = nullptr;
    std::string desc;

    order.id = "0f323156-ccb1-47a2-8164-d934c3e6a304";

    int http_status = order.httpSend(target, token, resJson,desc);

    if(http_status < 0)
    {
        std::cout << desc << "   " << http_status << std::endl;
        return -1;
    }

    std::cout << "http return " << http_status << std::endl;

    if(resJson)
    {
        std::cout << cJSON_Print(resJson.get()) << std::endl;
    }

    return 0;
}

int testRemoveSend()
{
    hfsh::RemoveSend order;
    std::shared_ptr<cJSON> resJson = nullptr;
    std::string desc;

    order.id = "2d829b3c-c1cd-4d43-a560-679398b8385a";

    int http_status = order.httpSend(target, token, resJson,desc);

    if(http_status < 0)
    {
        std::cout << desc << "   " << http_status << std::endl;
        return -1;
    }

    std::cout << "http return " << http_status << std::endl;

    if(resJson)
    {
        std::cout << cJSON_Print(resJson.get()) << std::endl;
    }

    return 0;
}

int testSendByProgramId()
{
    hfsh::SendByProgramId order;
    std::shared_ptr<cJSON> resJson = nullptr;
    std::string desc;

    order.id = "e7daca3d6bfe496cbfda0a02efe164e5";
    order.terminal_ids.push_back("W9AFNKCT");

    int http_status = order.httpSend(target, token, resJson,desc);

    if(http_status < 0)
    {
        std::cout << desc << "   " << http_status << std::endl;
        return -1;
    }

    std::cout << "http return " << http_status << std::endl;

    if(resJson)
    {
        std::cout << cJSON_Print(resJson.get()) << std::endl;
    }

    return 0;
}

int testSetVolumeTerminal()
{
  hfsh::SetVolumeTerminal order;
  std::shared_ptr<cJSON> resJson = nullptr;
  std::string desc;

  order.volume = 10;
  order.terminal_ids.push_back("W9AFNKCT");

  int http_status = order.httpSend(target, token, resJson,desc);

  if(http_status < 0)
  {
    std::cout << desc << "   " << http_status << std::endl;
    return -1;
  }

  std::cout << "http return " << http_status << std::endl;

  if(resJson)
  {
    std::cout << cJSON_Print(resJson.get()) << std::endl;
  }

  return 0;
}

int main()
try
{
    std::cout << "Hello, World!" << std::endl;

//1b87a749-d255-4adb-86b0-b767f03fe670
//b00f0475-0ddf-4867-a61b-0a1ccf1f7f71

    //testSendProgram();
    //testListProgram();
    //testCancelSend();
    //testRemoveSend();
    //testSendByProgramId();
    testSetVolumeTerminal();

    std::cout << "Hello, World--------------" << std::endl;
    return 0;
}
catch(const std::exception& e)
{
    std::cout << e.what() << std::endl;
    return 0;
}