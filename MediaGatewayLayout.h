#pragma once

#include <vector>
#include <string>

#include "CJson/json_reflection_utility.h"

struct MediaGatewayImage:JsonReflectionBase
{
    int x;
    int y;
    int width;
    int height;

    std::vector<std::string> files;

    REFLECT_WEBJSON_INPUT_ARGS_NUM(x, y, width, height, files)
    REFLECT_WEBJSON_OUTPUT_ARGS_NUM(x, y, width, height, files)
};

struct MediaGatewayVideo:JsonReflectionBase
{
    int x;
    int y;
    int width;
    int height;

    std::vector<std::string> files;

    REFLECT_WEBJSON_INPUT_ARGS_NUM(x, y, width, height, files)
    REFLECT_WEBJSON_OUTPUT_ARGS_NUM(x, y, width, height, files)
};

struct MediaGatewayAudio:JsonReflectionBase
{
    std::vector<std::string> files;
};

struct MediaGatewayText:JsonReflectionBase
{
    enum MoveDirection
    {
        Motionless, //��ֹ
        Left, //����
        Right,//����
        UP, //����
        Down //����
    };

    int x;
    int y;
    int width;
    int height;

    std::string text;
    std::string color;
    int fontSize;
    int direction; //��������
    int speed; //�����ٶ�

    REFLECT_WEBJSON_INPUT_ARGS_NUM(x, y, width, height, text, color,fontSize, direction, speed)
    REFLECT_WEBJSON_OUTPUT_ARGS_NUM(x, y, width, height, text, color,fontSize, direction, speed)

};

struct MediaGatewayWindow:JsonReflectionBase
{
    std::string program_id;

    int width;
    int height;

    int volume;

    std::vector<MediaGatewayImage> images;
    std::vector<MediaGatewayVideo> videos;
    std::vector<MediaGatewayAudio> audios;
    std::vector<MediaGatewayText> texts;

    REFLECT_WEBJSON_INPUT_ARGS_NUM(program_id, width, height, volume, images, videos,audios, texts)
    REFLECT_WEBJSON_OUTPUT_ARGS_NUM(program_id, width, height, volume, images, videos,audios, texts)
};





