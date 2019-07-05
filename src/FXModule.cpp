#include "FXModule.h"

FXModule::FXModule(std::string xfile, FXModule* in, ofFbo* loc){
  shaderString = "";

  if(moduleFile.loadFile(xfile)){
    if(moduleFile.tagExists("fragshader")){
      shaderString = moduleFile.getValue("fragshader","");
    }
    /*
    if(moduleFile.getNumTags("control")){ //get controls for uniforms
      controls.clear();
      std::vector<paramControl>::iterator it = controls.begin();
      for(int i = 0; i < moduleFile.getNumTags("control"); i++){
        if(moduleFile.getAttribute('control', 'type', "", i) == "int"){ //add control for int uniform. TODO: add one of these conditionals for each type of uniform.
          moduleFile.pushTag("control", i);
          int defaultValue = moduleFile.getValue("default", 0);
          int minValue = moduleFile.getValue("min", 0);
          int maxValue = moduleFile.getValue("max", 0);
          string controlType = moduleFile.getValue("controlType", "");
          moduleFile.popTag();
          string paramName = moduleFile.getAttribute('control','name', "", i);
          controls.emplace_back(&(this->shaderMod), paramName, minValue, maxValue, defaultValue, controlType);
        }
        if(moduleFile.getAttribute('control', 'type', "", i) == "float"){
          moduleFile.pushTag("control", i);
          float defaultValue = moduleFile.getValue("default", 0.0);
          float minValue = moduleFile.getValue("min", 0.0);
          float maxValue = moduleFile.getValue("max", 0.0);
          string controlType = moduleFile.getValue("controlType", "");
          moduleFile.popTag();
          string paramName = moduleFile.getAttribute('control','name', "", i);
          controls.emplace_back(&(this->shaderMod), paramName, minValue, maxValue, defaultValue, controlType);
        }

      }
    }
    */
  }

  locationMap = loc;
  inputBuffer = in;
  x = loc->getWidth();
  y = loc->getHeight();
  inputBox = new shaderInput(&shaderString);
  outputBuffer.allocate(x, y, GL_RGBA32F);
}

FXModule::FXModule(std::string xfile, ofFbo* loc){
  shaderString = "";

  if(moduleFile.loadFile(xfile)){
    if(moduleFile.tagExists("fragshader")){
      shaderString = moduleFile.getValue("fragshader","");
    }
    /*
    if(moduleFile.getNumTags("control")){ //get controls for uniforms
      controls.clear();
      std::vector<paramControl>::iterator it = controls.begin();
      for(int i = 0; i < moduleFile.getNumTags("control"); i++){
        if(moduleFile.getAttribute('control', 'type', "", i) == "int"){ //add control for int uniform. TODO: add one of these conditionals for each type of uniform.
          moduleFile.pushTag("control", i);
          int defaultValue = moduleFile.getValue("default", 0);
          int minValue = moduleFile.getValue("min", 0);
          int maxValue = moduleFile.getValue("max", 0);
          string controlType = moduleFile.getValue("controlType", "");
          moduleFile.popTag();
          string paramName = moduleFile.getAttribute('control','name', "", i);
          controls.emplace_back(&(this->shaderMod), paramName, minValue, maxValue, defaultValue, controlType);
        }
        if(moduleFile.getAttribute('control', 'type', "", i) == "float"){
          moduleFile.pushTag("control", i);
          float defaultValue = moduleFile.getValue("default", 0.0);
          float minValue = moduleFile.getValue("min", 0.0);
          float maxValue = moduleFile.getValue("max", 0.0);
          string controlType = moduleFile.getValue("controlType", "");
          moduleFile.popTag();
          string paramName = moduleFile.getAttribute('control','name', "", i);
          controls.emplace_back(&(this->shaderMod), paramName, minValue, maxValue, defaultValue, controlType);
        }

      }
    }
    */
  }

  locationMap = loc;
  inputBuffer = NULL;
  x = loc->getWidth();
  y = loc->getHeight();
  inputBox = new shaderInput(&shaderString);
  outputBuffer.allocate(x, y, GL_RGBA32F);
}


void FXModule::updateShader(){
  //shaderMod.setupShaderFromSource( GL_VERTEX_SHADER, "" ); //Not sure if I need this
  shaderMod.setupShaderFromSource( GL_FRAGMENT_SHADER, shaderString );
  shaderMod.bindDefaults();
  shaderMod.linkProgram();
  hasShader = 1;
}

void FXModule::draw(){

  shaderMod.setUniformTexture("loc", locationMap->getTexture(),0);
  if (inputBuffer != NULL){
    shaderMod.setUniformTexture("in0", inputBuffer->outputBuffer.getTexture(),1);
  }
  outputBuffer.begin();
  shaderMod.begin();
  ofDrawRectangle(0,0,x,y);
  shaderMod.end();
  outputBuffer.end();

}

void FXModule::drawUI(){
  if (inputBox->draw()){
    this->updateShader();
  }
}
