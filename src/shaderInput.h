#pragma once
#include "ofxImGui.h"
#include <string>
class shaderInput{
public:
  shaderInput(std::string* shaderString);
  std::string* sourceString;
  bool isUpdated = false;
  char shaderCode[128*256];
  bool draw();
};
