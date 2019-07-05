#pragma once

#include "ofxImGui.h"
#include "FXChain.h"

class controlPanel{
public:
  FXChain* effectChain;
  void draw(FXChain** activeChain);
  controlPanel(FXChain* c);
};
