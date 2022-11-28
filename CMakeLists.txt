cmake_minimum_required(VERSION 3.22)
project(hf)

set(CMAKE_CXX_STANDARD 11)

find_package(Poco 1.9.4 REQUIRED COMPONENTS Foundation Net Zip)
find_package(Boost 1.72.0 REQUIRED COMPONENTS system filesystem)

include_directories(${Boost_INCLUDE_DIR})

file(GLOB sources CONFIGURE_DEPENDS CJson/*.cpp CJson/*.h CJson/*.hpp)

add_executable(${PROJECT_NAME} main.cpp ${sources} hfsh/OrderBase.cpp hfsh/OrderBase.h hfsh/SendProgram.cpp hfsh/SendProgram.h MediaGatewayLayout.cpp MediaGatewayLayout.h)

target_link_libraries(${PROJECT_NAME} PUBLIC Poco::Foundation Poco::Net Poco::Zip Boost::system Boost::filesystem)
