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
	//DStainedGlass _dsg;
	//DEgyptianVertical _dev;
	//DBreeze _dbr;
	DTemple _dtp;
	ofxPostProcessing _post;
	float _mainTimer;
};
