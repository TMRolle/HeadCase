#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ImGui::GetIO().MouseDrawCursor = false;
    ofFbo::Settings fboSettings;
    fboSettings.width = 128;
    fboSettings.height = 128;
    fboSettings.internalformat = GL_RGBA;
    fboSettings.textureTarget = GL_TEXTURE_2D;
    pixelLocationBuffer.allocate(fboSettings);
    pixelLocationBuffer.begin();
    ofClear(255,255,255,255);
    pixelLocationBuffer.end();
    pixelLocationBufferID = pixelLocationBuffer.getTexture().getTextureData().textureID;
    universalParameter = 0.5;
    fx1 = new FXChain(&universalParameter, "FX1", &pixelLocationBuffer);
    cp1 = new controlPanel(fx1);
    fx2 = new FXChain(&universalParameter, "FX2", &pixelLocationBuffer);
    cp2 = new controlPanel(fx2);
    for(int j = 0; j < 16; j++){
      fxArray[j] = new FXChain(&universalParameter, to_string(j), &pixelLocationBuffer);
      controlArray[j] = new controlPanel(fxArray[j]);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  gui.begin();
  static bool normalizepos = true;
  static bool normalizewatts = true;
  static bool openConfig = false;
  const string xmlFileName = "PixelSettings.xml";
  {
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(ofGetWidth(),ofGetHeight()), true);
    ImGui::Begin("Pixel String Loader", NULL, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Calibration"))
            {
                ImGui::MenuItem("Set Up Lighting Configuration", NULL, &openConfig);
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

    if(openConfig)
      {
      ImGui::OpenPopup("Lighting Configuration");
        if (ImGui::BeginPopupModal("Lighting Configuration"))
        {
          if(ImGui::Button("Load XML File")){
            ofApp::readPixelsFromXml(&pixelStringList, &xmlFile, xmlFileName);
            if(normalizepos){
              normalizeXYZ(&pixelStringList);
            }
            if(normalizewatts){
              normalizeWattage(&pixelStringList);
            }
          }

          ImGui::Checkbox("Normalize XYZ coordinates", &normalizepos);
          ImGui::Checkbox("Normalize Pixel Wattage", &normalizewatts);
          if(ImGui::Button("Load PixelString to Buffer")){
            const int xMax = pixelLocationBuffer.getWidth();
            const int yMax = pixelLocationBuffer.getHeight();
            float pixels[4 * xMax * yMax] = {};
            for(std::list<pixelString>::iterator iter = pixelStringList.begin(); iter != pixelStringList.end(); iter++){
              int addressloc = (iter->universe * 512 + iter->channelStart);
              for (int i = 0; i < iter->numPixels; i++){
                pixels[addressloc++] = ofLerp(iter->startLocation[0], iter->endLocation[0], (float)i / (float)iter->numPixels );
                pixels[addressloc++] = ofLerp(iter->startLocation[1], iter->endLocation[1], (float)i / (float)iter->numPixels );
                pixels[addressloc++] = ofLerp(iter->startLocation[2], iter->endLocation[2], (float)i / (float)iter->numPixels );
                pixels[addressloc++] = iter->wattsPerPixel;
              }
            }
            pixelLocationBuffer.getTexture().loadData(pixels, xMax, yMax, GL_RGBA32F);

          }
          ImGui::Image((ImTextureID)(uintptr_t)pixelLocationBufferID, ImVec2(pixelLocationBuffer.getWidth(),pixelLocationBuffer.getHeight()), ImVec2(0,0), ImVec2(1,1), ImColor(255,255,255,255), ImColor(255,255,255,128));
          ImGui::Spacing();
          if(ImGui::Button("Done")){
            openConfig = 0;
            ImGui::CloseCurrentPopup();
          }

          ImGui::EndPopup();
        }
      }
    ImGui::BeginChild("MasterCP", ImVec2(ImGui::GetContentRegionAvailWidth() / 9,ImGui::GetContentRegionAvail().y * 0.62), false);
      ImGui::VSliderFloat("##v", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), &masterFader, 0.0f, 1.0f, "M\na\ns\nt\ne\nr");
      ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("Perform", ImVec2(ImGui::GetContentRegionAvailWidth(), ImGui::GetContentRegionAvail().y * 0.62), false);
      /*cp1->draw();
      ImGui::SameLine();
      cp2->draw();
      */
      for(int j = 0; j < 16; j++){
        controlArray[j]->draw(&activeChain);
        if(j!=7){
        ImGui::SameLine();
        }
      }
      ImGui::EndChild();
    ImGui::BeginChild("Module Editor", ImVec2(ImGui::GetContentRegionAvailWidth() / 4.5, ImGui::GetContentRegionAvail().y), false);
      ImGui::Button("sup");
      ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("Chain Editor", ImGui::GetContentRegionAvail(), false);
      if (activeChain != NULL){
        activeChain->drawUI();
      }
      ImGui::EndChild();
    ImGui::End();
  }
  gui.end();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

bool ofApp::readPixelsFromXml(std::list<pixelString>* listToWrite, ofxXmlSettings* ofxXmlObject, const string filename){
  ofxXmlObject->clear();
  if(ofxXmlObject->loadFile(filename)){

    listToWrite->clear();

    int numLEDs = ofxXmlObject->getNumTags("LEDString");

    for(int i = 0; i < numLEDs; i++){
      ofxXmlObject->pushTag("LEDString", i);
        string na = ofxXmlObject->getValue("Name","");
        int u = ofxXmlObject->getValue("Universe",0);
        int c = ofxXmlObject->getValue("ChannelStart", 0);
        int n = ofxXmlObject->getValue("NumPixels", 0);
        ofxXmlObject->pushTag("StartPostion");
          float start[3];
          start[0] = ofxXmlObject->getValue("X", 0.0);
          start[1] = ofxXmlObject->getValue("Y", 0.0);
          start[2] = ofxXmlObject->getValue("Z", 0.0);
        ofxXmlObject->popTag();
        ofxXmlObject->pushTag("EndPostion");
          float end[3];
          end[0] = ofxXmlObject->getValue("X", 0.0);
          end[1] = ofxXmlObject->getValue("Y", 0.0);
          end[2] = ofxXmlObject->getValue("Z", 0.0);
        ofxXmlObject->popTag();
        float w = ofxXmlObject->getValue("WattsPerPixel", 0.0);
      ofxXmlObject->popTag();
      listToWrite->emplace_back(na, u, c, n, start, end, w);
    }
    return true;
  }
    return false;
}

bool ofApp::normalizeXYZ(std::list<pixelString>* listToNormalize){
  float maxValue = 0;
  if (listToNormalize->size() == 0){
    return false;
  }
  for(std::list<pixelString>::iterator iter = listToNormalize->begin(); iter != listToNormalize->end(); iter++) //get the maximum coordinate in any direction
  {
      for(int i = 0; i < 3; i++)
      {
        if(maxValue < iter->startLocation[i])
        {
          maxValue = iter->startLocation[i];
        }
        if(maxValue < iter->endLocation[i])
        {
          maxValue = iter->endLocation[i];
        }
      }

  }
  for(std::list<pixelString>::iterator iter = listToNormalize->begin(); iter != listToNormalize->end(); iter++) //Scale uniformly to max coordinate in any direction
  {
      for(int i = 0; i < 3; i++)
      {
        iter->startLocation[i] = ofClamp(iter->startLocation[i] / maxValue,0.0,1.0);
        iter->endLocation[i] = ofClamp(iter->endLocation[i] / maxValue,0.0,1.0);
      }

  }
  return true;
}
bool ofApp::normalizeWattage(std::list<pixelString>* listToNormalize){
  float maxValue = 0;
  if (listToNormalize->size() == 0){
    return false;
  }
  for(std::list<pixelString>::iterator iter = listToNormalize->begin(); iter != listToNormalize->end(); iter++) //get the maximum coordinate in any direction
  {
        if(maxValue < iter->wattsPerPixel)
        {
          maxValue = iter->wattsPerPixel;
        }

  }
  for(std::list<pixelString>::iterator iter = listToNormalize->begin(); iter != listToNormalize->end(); iter++) //Scale uniformly to max coordinate in any direction
  {
        iter->wattsPerPixel = ofClamp(iter->wattsPerPixel / maxValue, 0.0,1.0);
  }
  return true;
}
