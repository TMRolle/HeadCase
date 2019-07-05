#pragma once

class paramControl{

public:
  ofShader* shader;
  virtual void setUniform();
  virtual void drawPanel();
};
