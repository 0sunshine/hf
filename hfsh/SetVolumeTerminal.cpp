//
// Created by Administrator on 2022/11/24.
//

#include "SetVolumeTerminal.h"


namespace hfsh {

SetVolumeTerminal::SetVolumeTerminal():volume(0)
{
  _service = "terminal";
  _method = "setVolume";
}

int SetVolumeTerminal::httpSend(const OrderTarget& target,const std::string& token, std::shared_ptr<cJSON>& resJson,std::string& desc)
{
  _textSources["volume"] = std::to_string(volume);

  std::string id_array;

  for(auto& x : terminal_ids)
  {
    id_array += '\"' + x +'\"' + ',';
  }

  if(!id_array.empty())
  {
    id_array.pop_back();
  }

  _textSources["data"] = "[" + id_array + "]";

  return OrderRequest::httpSend(target, token, resJson,desc);
}


}