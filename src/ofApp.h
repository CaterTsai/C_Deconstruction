#pragma once

#include "ofMain.h"
#include "DRomanCircle.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	ofEasyCam _cam;
	DRomanCircle _drc;
	float _mainTimer;
};
