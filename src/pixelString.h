#pragma once

#include <string>

class pixelString
{
  public:
  char name[64];
  int universe;
  int channelStart;
  int numPixels;
  float startLocation[3];
  float endLocation[3];
  float wattsPerPixel;
  pixelString(std::string na, int u, int c, int n, float *start, float *end, float w);
  pixelString();
};
