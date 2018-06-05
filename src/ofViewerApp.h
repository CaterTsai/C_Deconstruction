#pragma once

#include "constParameter.h"
#include "displayMgr.h"


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
