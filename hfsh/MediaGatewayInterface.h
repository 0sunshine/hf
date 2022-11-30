#pragma once

#include "../MediaGatewayLayout.h"

#include <boost/optional.hpp>

namespace hfsh
{

struct CreateProgramRequest:JsonReflectionBase
{
  MediaGatewayWindow window;

  REFLECT_WEBJSON_INPUT_ARGS_NUM(window)
  REFLECT_WEBJSON_OUTPUT_ARGS_NUM(window)
};

struct CreateProgramResponse:JsonReflectionBase
{
  int code;
  std::string desc;
  std::string program_id;

  REFLECT_WEBJSON_INPUT_ARGS_NUM(code,desc,program_id)
  REFLECT_WEBJSON_OUTPUT_ARGS_NUM(code,desc,program_id)
};

struct PlayProgramRequest:JsonReflectionBase
{
  std::vector<std::string> terminal_ids;
  std::string program_id;
  int volume;

  REFLECT_WEBJSON_INPUT_ARGS_NUM(terminal_ids,program_id,volume)
  REFLECT_WEBJSON_OUTPUT_ARGS_NUM(terminal_ids,program_id,volume)
};

struct PlayProgramResponse:JsonReflectionBase
{
  int code;
  std::string desc;

  std::vector<std::string> play_ids;

  REFLECT_WEBJSON_INPUT_ARGS_NUM(code,desc,play_ids)
  REFLECT_WEBJSON_OUTPUT_ARGS_NUM(code,desc,play_ids)
};

struct StopProgramRequest:JsonReflectionBase
{
  std::vector<std::string> play_ids;

  REFLECT_WEBJSON_INPUT_ARGS_NUM(play_ids)
  REFLECT_WEBJSON_OUTPUT_ARGS_NUM(play_ids)
};

struct StopProgramResponse:JsonReflectionBase
{
  int code;
  std::string desc;

  REFLECT_WEBJSON_INPUT_ARGS_NUM(code,desc)
  REFLECT_WEBJSON_OUTPUT_ARGS_NUM(code,desc)
};


struct Protocol
{
  boost::optional<CreateProgramRequest> createProgramRequest;
  boost::optional<CreateProgramResponse> createProgramResponse;

  boost::optional<PlayProgramRequest> playProgramRequest;
  boost::optional<PlayProgramResponse> playProgramResponse;

  boost::optional<StopProgramRequest> stopProgramRequest;
  boost::optional<StopProgramResponse> stopProgramResponse;


  REFLECT_WEBJSON_INPUT_ARGS_NUM
  (
      createProgramRequest,createProgramResponse,
      playProgramRequest,playProgramResponse,
      stopProgramRequest,stopProgramResponse
  )

  REFLECT_WEBJSON_OUTPUT_ARGS_NUM
  (
      createProgramRequest,createProgramResponse,
      playProgramRequest,playProgramResponse,
      stopProgramRequest,stopProgramResponse
  )
};


}




