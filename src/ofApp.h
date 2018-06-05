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

	float _mainTimer;
};
