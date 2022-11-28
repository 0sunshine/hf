#include <iostream>

#include "hfsh/SendProgram.h"
#include "MediaGatewayLayout.h"

const hfsh::OrderTarget target {"192.168.22.120",9101};
const std::string& token = "123456";

int testPicture()
{
    MediaGatewayWindow window;
    window.program_id = u8"我擦xxx2222";
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




int main()
try
{
    std::cout << "Hello, World!" << std::endl;


    testPicture();


    std::cout << "Hello, World--------------" << std::endl;
    return 0;
}
catch(const std::exception& e)
{
    std::cout << e.what() << std::endl;
    return 0;
}