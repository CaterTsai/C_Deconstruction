#pragma once

#include "ofMain.h"
#include "shaderVoronoi.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void mousePressed(int x, int y, int button);
		
private:
	void setupVoronoi();
	void updateVoronoi();
	void drawVoronoi();

private:
	bool _drawImg;
	shaderVoronoi _voronoi;
	ofImage	_img;
};
