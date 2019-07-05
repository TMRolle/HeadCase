#include "shaderInput.h"

shaderInput::shaderInput(std::string* shaderString){
  sourceString = shaderString;
}

bool shaderInput::draw(){
  isUpdated = false;
  ImGui::BeginGroup();
  ImGui::PushID(this);
  ImGui::BeginChild(ImGui::GetID(this), ImVec2((ImGui::GetContentRegionMax().x / 8)-ImGui::GetStyle().FramePadding.x*2, (ImGui::GetContentRegionMax().y /2)-ImGui::GetStyle().FramePadding.y*2), false);
  ImGui::InputTextMultiline("##SourceInput", shaderCode, (128*256), ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16), ImGuiInputTextFlags_AllowTabInput);
  if(ImGui::Button("Upload")){
    *sourceString = shaderCode;
    isUpdated = true;
  }
  ImGui::EndChild();
  ImGui::PopID();
  ImGui::EndGroup();
  return isUpdated;

}
