#include "controlPanel.h"

void controlPanel::draw(FXChain** activeChain)
{
  ImGui::BeginGroup();
  ImGui::PushID(effectChain);
  ImGui::BeginChild(ImGui::GetID(effectChain), ImVec2((ImGui::GetContentRegionMax().x / 8)-ImGui::GetStyle().FramePadding.x*2, (ImGui::GetContentRegionMax().y /2)-ImGui::GetStyle().FramePadding.y*2), false);
    ImGui::BeginChild("#namePanel", ImVec2(ImGui::GetContentRegionAvailWidth(),30), false);
      ImGui::Button(effectChain->name.c_str(), ImVec2(ImGui::GetContentRegionAvailWidth()*0.75,ImGui::GetContentRegionAvail().y));
      ImGui::SameLine();
      ImGui::Button("V",ImVec2(ImGui::GetContentRegionAvailWidth(),ImGui::GetContentRegionAvail().y));
    ImGui::EndChild();
    ImGui::BeginChild("#MasterFaderChild", ImVec2(30,ImGui::GetContentRegionAvail().y), false);
      ImGui::VSliderFloat("##v", ImGui::GetContentRegionAvail(), &effectChain->master, 0.0f, 1.0f, "E\nf\nf\ne\nc\nt");
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("#ContentRegionChild", ImVec2(ImGui::GetContentRegionAvailWidth(),ImGui::GetContentRegionAvail().y), false);
      ImGui::PushItemWidth(ImGui::GetWindowWidth());
      ImGui::SliderFloat("##cParam", &effectChain->cParam, 0.0f, 1.0f, "Parameter");
      ImGui::SliderFloat("##uParam", effectChain->uParam, 0.0f, 1.0f, "Universal");
      ImGui::PopItemWidth();
      //ImGui::Image((ImTextureID)(uintptr_t)pixelLocationBufferID, ImVec2(100,100), ImVec2(0,0), ImVec2(1,1), ImColor(255,255,255,255), ImColor(255,255,255,128));
      ImGui::Button("Save");
      ImGui::SameLine();
      ImGui::Button("Load");
    ImGui::EndChild();
  ImGui::EndChild();
  ImGui::PopID();
  ImGui::EndGroup();
  if(ImGui::IsItemClicked()){
    *activeChain = effectChain;
  }
}

controlPanel::controlPanel(FXChain* c){
  effectChain = c;
}
