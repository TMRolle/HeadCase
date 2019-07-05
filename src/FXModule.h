#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "shaderInput.h"
#include <string>

class FXModule
{
public:
  FXModule(std::string xfile, FXModule* in, ofFbo* loc);
  FXModule(std::string xfile, ofFbo* loc);
  int x;
  int y;
  shaderInput* inputBox;
  ofShader shaderMod;
  ofFbo outputBuffer;
  ofFbo* locationMap;
  FXModule* inputBuffer;
  //std::vector<paramControl> controls;
  ofxXmlSettings moduleFile;
  std::string shaderString;
  void updateShader();
  void draw();
  void drawUI();
  bool hasShader = 0;
};
