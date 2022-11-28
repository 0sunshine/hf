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

struct MediaGatewayText
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
    std::vector<MediaGatewayText> texts;
};





