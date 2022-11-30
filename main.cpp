
#include <iostream>
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>
#include <chrono>

#include "./mylog.h"

using namespace std;

#include "hfsh/MediaGatewayHandler.h"

using boost::asio::ip::tcp;

const int max_length = 1024*16;

void session(tcp::socket sock)
{
    std::cout << "new connection " <<  std::endl;
    std::shared_ptr<void> raii_log((void*)1, [](void*) {
      std::cout << "disconnection " << std::endl;
    });
    try
    {
        for (;;)
        {
            char data[max_length];
            std::string all_data;

            while (true)
            {
                boost::system::error_code error;

                auto can_read = sock.available(error);
                int wait_times = 100;

                while (can_read <= 0 && !error)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    can_read = sock.available(error);
                    --wait_times;
                    if (wait_times < 0)
                    {
                        TRACE_LOG_A(nullptr, TRACE_LOG_LEVEL_ERROR, "request timeout");
                        return;
                    }
                }

                size_t length = 0;

                if (!error)
                {
                    length = sock.read_some(boost::asio::buffer(data), error);
                }

                if (error == boost::asio::error::eof)
                    break; // Connection closed cleanly by peer.
                else if (error)
                    throw boost::system::system_error(error); // Some other error.

                all_data += std::string(data, length);

                auto pos = all_data.find('\0');
                if (pos != std::string::npos) //完整一条
                {
                    cJSON* json = cJSON_Parse(all_data.c_str());
                    if (json == nullptr)
                    {
                        TRACE_LOG_A(nullptr, TRACE_LOG_LEVEL_ERROR, "invailed json");
                        return;
                    }

                    hfsh::Protocol input;
                    bool parse_ok = input.parseWebJsonInput(json);
                    if (!parse_ok)
                    {
                        TRACE_LOG_A(nullptr, TRACE_LOG_LEVEL_ERROR, "parse hfsh::Protocol failed");
                        return;
                    }

                    hfsh::Protocol output;
                    if( !hfsh::hander(input,output) )
                    {
                        TRACE_LOG_A(nullptr, TRACE_LOG_LEVEL_ERROR, "handler hfsh::Protocol failed, %s", all_data.c_str());
                        return;
                    }


                    cJSON* responseJson = output.genarateWebJsonOutput();
                    if (responseJson == nullptr)
                    {
                        TRACE_LOG_A(nullptr, TRACE_LOG_LEVEL_ERROR, "gen hfsh::Protocol failed");
                        return;
                    }

                    std::string resString = JsonHandler::JsonToString(responseJson);
                    resString += '\0';

                    auto send_bytes = boost::asio::write(sock, boost::asio::buffer(resString));

                    return;
                }
                else
                {
                    continue;
                }

            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in session: " << e.what() << "\n";
    }
}

void server(boost::asio::io_context& io_context, unsigned short port)
{
    tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
    for (;;)
    {
        session(a.accept());
    }
}

int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_context io_context;
        server(io_context, 7943);
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\nexit....";
        std::this_thread::sleep_for( std::chrono::seconds(10));
    }

    return 0;
}

