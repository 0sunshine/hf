//
// Created by Administrator on 2022/11/24.
//

#include "SendProgram.h"
#include "../CJson/json_reflection_utility.h"

#include <fstream>
#include <iostream>
#include <Poco/Zip/Compress.h>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/DateTime.h>
#include <Poco/Zip/ZipException.h>
#include <Poco/FileStream.h>


namespace hfsh {

SendProgram::SendProgram() {
    _service = "send";
    _method = "sendProgram";
}

int SendProgram::setMediaGatewayWindow(const MediaGatewayWindow &window) {
    _window = window;
    return 0;
}

//按照文档定义结构体
struct ElementItem:JsonReflectionBase
{
    boost::optional<std::string> src;
    boost::optional<int> len;
    boost::optional<int> volume;
    boost::optional<std::string> content;
    boost::optional<std::string> color;
    boost::optional<std::string> backColor;
    boost::optional<std::string> fontSize;
    boost::optional<int> bold;
    boost::optional<int> italic;
    boost::optional<int> underline;
    boost::optional<int> strikeout;
    boost::optional<int> transparent;
    boost::optional<int> direction;
    boost::optional<int> speed;

    REFLECT_WEBJSON_OUTPUT_ARGS_NUM(src,len,volume,content,color,
                                    backColor,fontSize,bold,italic,underline,
                                    strikeout,transparent,direction,speed)
};

struct Element:JsonReflectionBase
{
    std::string type;
    int left;
    int top;
    int width;
    int height;

    std::vector<ElementItem> items;

    REFLECT_WEBJSON_OUTPUT_ARGS_NUM(type,left,top,width,height,items)
};

struct Program
{
    std::string beginDate;
    std::string endDate;
    std::string beginTime;
    std::string endTime;
    std::vector<int> weeks;
    std::vector<std::string> terminalIds;
    std::string name;
    int width;
    int height;
    int priority;
    boost::optional<std::string> background;

    std::vector<Element> elements;

REFLECT_WEBJSON_OUTPUT_ARGS_NUM(beginDate,endDate,beginTime,endTime,weeks,
                                terminalIds,name,width,height,priority,
                                background,elements)
};

int handleImage(Program& program, const std::vector<MediaGatewayImage>& images, const Poco::File& program_files_dir, std::string& desc)
{
    for (const auto &image: images) {
        Element image_element;
        image_element.type = "picture";
        image_element.left = image.x;
        image_element.top = image.y;
        image_element.width = image.width;
        image_element.height = image.height;

        for (const auto &f: image.files)
        {
            Poco::File res(f);
            if (!res.exists() || res.isDirectory())
            {
                desc = f + " not exists or it is a directory";
                return -1;
            }
            res.copyTo(program_files_dir.path());

            ElementItem item;
            item.src = Poco::Path(f).getFileName();
            item.len = 5;
            image_element.items.push_back(item);
        }

        program.elements.push_back(image_element);
    }

    return 0;
}

int handleVideo(Program& program, const std::vector<MediaGatewayVideo>& videos, const Poco::File& program_files_dir, std::string& desc)
{
    for (const auto &video: videos) {
        Element video_element;
        video_element.type = "video";
        video_element.left = video.x;
        video_element.top = video.y;
        video_element.width = video.width;
        video_element.height = video.height;

        for (const auto &f: video.files)
        {
            Poco::File res(f);
            if (!res.exists() || res.isDirectory())
            {
                desc = f + " not exists or it is a directory";
                return -1;
            }
            res.copyTo(program_files_dir.path());

            ElementItem item;
            item.src = Poco::Path(f).getFileName();
            item.len = 5;
            video_element.items.push_back(item);
        }

        program.elements.push_back(video_element);
    }

    return 0;
}

int handleAudio(Program& program, const std::vector<MediaGatewayAudio>& audios, const Poco::File& program_files_dir, std::string& desc)
{
    for (const auto &audio: audios) {
        Element audio_element;
        audio_element.type = "video";
        audio_element.left = 0;
        audio_element.top = 0;
        audio_element.width = 0;
        audio_element.height = 0;

        for (const auto &f: audio.files)
        {
            Poco::File res(f);
            if (!res.exists() || res.isDirectory())
            {
                desc = f + " not exists or it is a directory";
                return -1;
            }
            res.copyTo(program_files_dir.path());

            ElementItem item;
            item.src = Poco::Path(f).getFileName();
            item.len = 5;
            audio_element.items.push_back(item);
        }

        program.elements.push_back(audio_element);
    }

    return 0;
}

int handleText(Program& program, const std::vector<MediaGatewayText>& texts, const Poco::File&, std::string& desc)
{
    for (const auto &text: texts)
    {
        Element text_element;
        text_element.type = "text";
        text_element.left = text.x;
        text_element.top = text.y;
        text_element.width = text.width;
        text_element.height = text.height;

        ElementItem item;
        item.content = text.text;
        item.color = text.color;
        item.backColor = "#ffffff";
        item.fontSize = std::to_string(text.fontSize);
        item.bold = 0;
        item.italic = 0;
        item.underline = 0;
        item.strikeout = 0;
        item.transparent = 1;

        if(MediaGatewayText::Left == text.direction)
        {
            item.direction = 2;
        }
        else if(MediaGatewayText::Right == text.direction)
        {
            item.direction = 1;
        }
        else if(MediaGatewayText::UP == text.direction)
        {
            item.direction = 4;
        }
        else if(MediaGatewayText::Down == text.direction)
        {
            item.direction = 3;
        }
        else
        {
            item.direction = 0;
        }

        item.speed = text.speed;

        text_element.items.push_back(item);

        program.elements.push_back(text_element);
    }

    return 0;
}

int SendProgram::httpSend(const OrderTarget &target, const std::string &token, std::shared_ptr<cJSON> &resJson,
                          std::string &desc) {
    try
    {
        //专门处理节目的目录
        static const std::string &base_dir = "./";

        Poco::File program_dir(base_dir + _window.program_id);

        //清空节目文件夹
        if (program_dir.exists()) {
            program_dir.remove(true);
        }
        program_dir.createDirectory();

        Poco::File program_files_dir(program_dir.path() + "/files");
        program_files_dir.createDirectories();

        //创建json
        std::shared_ptr<cJSON> pJson(cJSON_CreateObject(),[](cJSON* ptr){
            cJSON_Delete(ptr);
        });

        Program program;

        program.beginDate = "2000-01-11";
        program.endDate = "2100-01-12";
        program.beginTime = "00:11:11";
        program.endTime = "22:11:12";

        program.weeks = std::vector<int>{1,2,3,4,5,6,0};
        program.terminalIds = std::vector<std::string>{"W9AFNKCT"};
        program.name = _window.program_id;
        program.width = _window.width;
        program.height = _window.height;
        program.priority = 1;

        //复制所需文件及填充json结构

        //图片
        int handle_ret = handleImage(program,_window.images,program_files_dir,desc);
        if( 0 != handle_ret )
        {
            return handle_ret;
        }

        //视频
        handle_ret = handleVideo(program,_window.videos,program_files_dir,desc);
        if( 0 != handle_ret )
        {
            return handle_ret;
        }

        //音频
        handle_ret = handleAudio(program,_window.audios,program_files_dir,desc);
        if( 0 != handle_ret )
        {
            return handle_ret;
        }

        //文字
        handle_ret = handleText(program,_window.texts,program_files_dir,desc);
        if( 0 != handle_ret )
        {
            return handle_ret;
        }

        //创建program.json
        cJSON* program_json = program.genarateWebJsonOutput();
        if(program_json == nullptr)
        {
            desc = "生成program.json失败";
            return -1;
        }

        std::string json_text = JsonHandler::JsonToString(program_json);
        cJSON_Delete(program_json);

        const std::string &program_file = program_dir.path() + "/program.json";

        Poco::FileOutputStream program_file_out(program_file);
        if (!program_file_out)
        {
            desc = "create failed: " + program_file;
            return -1;
        }
        program_file_out.write(json_text.c_str(), json_text.size());
        program_file_out.close();

        //创建压缩文件
        const std::string &zip_file = base_dir + _window.program_id + ".zip";
        Poco::FileOutputStream out(zip_file, std::ios::binary | std::ios::ate);
        if (!out)
        {
            desc = "create failed: " + zip_file;
            return -1;
        }

        //添加进压缩包
        std::shared_ptr<Poco::Zip::Compress> c(new Poco::Zip::Compress(out, true), [](Poco::Zip::Compress *ptr) {
            ptr->close();
            delete ptr;
        });

        c->addRecursive(program_dir.path(), Poco::Zip::ZipCommon::CL_MAXIMUM);

        c->close();

        out.close();

        _fileSources["files"] = zip_file;

        return OrderRequest::httpSend(target, token, resJson, desc);
    }
    catch (const Poco::Exception &e) {
        desc = e.displayText();
        return -1;
    }
    catch (const std::exception &e) {
        desc = e.what();
        return -1;
    }

    return 0;
}

}