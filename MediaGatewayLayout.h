#pragma once

#include <vector>
#include <string>

struct MediaGatewayImage
{
    int x;
    int y;
    int width;
    int height;

    std::vector<std::string> files;

};

struct MediaGatewayVideo
{
    int x;
    int y;
    int width;
    int height;

    std::vector<std::string> files;
};

struct MediaGatewayAudio
{
    std::vector<std::string> files;
};

struct MediaGatewayWindow
{
    std::string program_id;

    int width;
    int height;

    int volume;

    std::vector<MediaGatewayImage> images;
    std::vector<MediaGatewayVideo> videos;
    std::vector<MediaGatewayAudio> audios;

};





