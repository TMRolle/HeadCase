#pragma once

#include <list>
#include <string>
#include <vector>

#include "FXModule.h"
#include "ofMain.h"
#include "ofxXmlSettings.h"

class FXChain
{
public:
  std::string name;
  float master;
  float cParam;
  float* uParam;
  std::list<FXModule> chain;
  ofxXmlSettings xmlConfig;
  ofFbo* locationMap;
  std::vector<ofFbo> buffers;
  ofFbo output;
  FXChain(float* u, std::string n, ofFbo* l);
  FXChain(float* u, ofxXmlSettings* f, ofFbo* l);
  ofFbo* draw();
  void drawUI();
};
