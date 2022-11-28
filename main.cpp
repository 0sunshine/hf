#include <iostream>

#include "hfsh/SendProgram.h"
#include "MediaGatewayLayout.h"

int main()
try
{
    std::cout << "Hello, World!" << std::endl;

    const hfsh::OrderTarget target {"192.168.22.120",9101};
    const std::string& token = "123456";

    MediaGatewayWindow window;
    window.program_id = "我擦";
    window.width = 1920;
    window.height = 1080;

    MediaGatewayImage image1;
    image1.width = 800;
    image1.height = 800;
    image1.x = 100;
    image1.y = 100;
    image1.files.push_back("d:/test_led.jpg");

    window.images.push_back(image1);

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

    std::cout << "Hello, World--------------" << std::endl;
    return 0;
}
catch(const std::exception& e)
{
    std::cout << e.what() << std::endl;
    return 0;
}