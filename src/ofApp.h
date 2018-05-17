#pragma once

#include "ofMain.h"
#include "drawer.h"
#include "ofxPostProcessing.h"
#include "postFilter.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	ofEasyCam _cam;
	//DRomanCircle _drc;
	DStainedGlass _dsg;

	ofxPostProcessing _post;
	float _mainTimer;
};
