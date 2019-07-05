#include "pixelString.h"

pixelString::pixelString(std::string na, int u, int c, int n, float *start, float *end, float w)
{
  sprintf(name,"%s\n", na.c_str());
  universe = u;
  channelStart = c;
  numPixels = n;
  for(int i = 0; i < 3; i++){
    startLocation[i] = start[i];
  }
  for(int i = 0; i < 3; i++){
    endLocation[i] = end[i];
  }
  wattsPerPixel = w;
}
pixelString::pixelString()
{
  sprintf(name, "String");
  universe = 0;
  channelStart = 0;
  numPixels = 0;
  for(int i = 0; i < 3; i++){
    startLocation[i] = 0;
  }
  for(int i = 0; i < 3; i++){
    endLocation[i] = 0;
  }
  wattsPerPixel = 0;
}
