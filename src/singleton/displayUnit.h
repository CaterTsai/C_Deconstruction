#pragma once

#include "../constParameter.h"

struct stDisplayParam
{
	ofVec2f ctrlPos[cCtrlPointNum];
};

class displayUnit
{

#pragma region Basic
public:
	displayUnit();
	void setup(int width, int height, const stDisplayParam& param);

	void drawBegin(bool needClear = true);
	void drawEnd();
	void drawCanvas(int x, int y, int w, int h);

	ofRectangle getSize();
	ofVec2f getCtrlPos(int id);

private:
	bool _isSetup, _startDraw;
	ofFbo _canvas;
#pragma endregion
	
#pragma region Projection
//on projection
public:
	void drawOnProjection();
	void mousePress(int x, int y);
	void mouseDrag(int x, int y);
	void mouseRelease(int x, int y);
	void drawCtrlPos();
private:
	void setupPlane(int width, int height);

private:
	int _selectCtrlIndex;
	ofVec2f _ctrlPos[cCtrlPointNum];
	ofMesh _plane;
#pragma endregion



};