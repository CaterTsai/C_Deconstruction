#pragma once

#include "constParameter.h"
#include "displayMgr.h"
#include "camCtrl.h"
#include "postFilter.h"
#include "videoMgr.h"
#include "midiCtrl.h"

#include "scene.h"

class ofViewerApp : public ofBaseApp {

public:

	ofViewerApp()
	{}

	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);

private:
	bool _showMsg;
	float _mainTimer;

};
