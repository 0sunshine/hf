cmake_minimum_required(VERSION 3.22)
project(hf)

set(CMAKE_CXX_STANDARD 11)

find_package(Poco 1.9.4 REQUIRED COMPONENTS Foundation Net Zip)
find_package(Boost 1.72.0 REQUIRED COMPONENTS system filesystem)

include_directories(${Boost_INCLUDE_DIR})

file(GLOB sources CONFIGURE_DEPENDS CJson/*.cpp CJson/*.h CJson/*.hpp hfsh/*.h hfsh/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${sources} MediaGatewayLayout.cpp MediaGatewayLayout.h MediaGatewayInterface.cpp MediaGatewayInterface.h)

target_link_libraries(${PROJECT_NAME} PUBLIC Poco::Foundation Poco::Net Poco::Zip Boost::system Boost::filesystem)
