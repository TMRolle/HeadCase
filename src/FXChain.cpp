#include "FXChain.h"


FXChain::FXChain(float* u, std::string n, ofFbo* l){
    uParam = u;
    name = n;
    locationMap = l;
}

FXChain::FXChain(float* u, ofxXmlSettings* f, ofFbo* l){
  uParam = u;
  locationMap = l;
}
ofFbo* FXChain::draw(){
  ofFbo* endFbo = NULL;
  for(std::list<FXModule>::iterator iter = chain.begin(); iter != chain.end(); iter++){
    iter->draw();
    endFbo = &iter->outputBuffer;
  }
  return endFbo;
}

void FXChain::drawUI(){
  for(std::list<FXModule>::iterator iter = chain.begin(); iter != chain.end(); iter++){
    if(ImGui::Button("Add")){
      chain.emplace_back("",locationMap);
    }
    ImGui::SameLine();
    iter->drawUI();
    ImGui::SameLine();
  }
  if(ImGui::Button("Add")){
    chain.emplace_back("",locationMap);
  }
}
