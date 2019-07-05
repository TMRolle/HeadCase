#pragma once

#include "ofMain.h"
#include <list>
#include <string>
#include "ofxImGui.h"
#include "pixelString.h"
#include "ofxXmlSettings.h"
#include "FXChain.h"
#include "FXModule.h"
#include "controlPanel.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxXmlSettings xmlFile;
		ofxImGui::Gui gui;
		std::list<pixelString> pixelStringList;


		bool readPixelsFromXml(std::list<pixelString>* listToWrite, ofxXmlSettings* ofxXmlObject, const string filename);
		bool normalizeXYZ(std::list<pixelString>* listToNormalize);
		bool normalizeWattage(std::list<pixelString>* listToNormalize);

		ofFbo pixelLocationBuffer;
		GLuint pixelLocationBufferID;

		float universalParameter;

		FXChain* fx1;
		controlPanel* cp1;
		FXChain* fx2;
		controlPanel* cp2;

		FXChain* fxArray[16];
		controlPanel* controlArray[16];
		FXChain* activeChain = NULL;

		float masterFader = 0.5;

};
