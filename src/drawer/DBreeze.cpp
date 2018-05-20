#include "DBreeze.h"

//--------------------------------------
void DBreeze::update(float delta)
{
	CHECK_START();
}

//--------------------------------------
void DBreeze::draw()
{
	CHECK_START();

	displayFlow(0, 0, cWindowWidth, cWindowHeight);
}

//--------------------------------------
void DBreeze::start()
{
	generateFlowFields();
	_isStart = true;
}

//--------------------------------------
void DBreeze::stop()
{
	_isStart = false;
}

//--------------------------------------
void DBreeze::trigger(int key)
{
}

//--------------------------------------
void DBreeze::generateFlowFields()
{
	float offset = 0.05;
	for (int i = 0; i < cFieldRows; i++)
	{
		for (int j = 0; j < cFieldCols; j++)
		{
			//float theta = ofMap(ofNoise(i * offset, j * offset), 0, 1, 0, TWO_PI);
			float theta = ofRandom(-PI / 4.0f, PI / 4.0f);
			ofVec2f desired(cos(theta), sin(theta));
			_flowFields[i][j].set(desired.normalized());
		}
	}
}

//--------------------------------------
void DBreeze::displayFlow(int x, int y, int w, int h)
{
	ofPushStyle();
	ofSetColor(255);
	ofFill();
	float unitW, unitH;
	unitW = w / cFieldCols;
	unitH = h / cFieldRows;

	for (int i = 0; i < cFieldRows; i++)
	{
		for (int j = 0; j < cFieldCols; j++)
		{
			ofVec2f center(j * unitW + unitW * 0.5, i * unitH + unitH * 0.5);
			ofVec2f desired = _flowFields[i][j];
			ofVec2f end = center + (desired * 0.5 * unitW);

			ofDrawCircle(center, 0.2 * unitW);
			ofLine(center, end);
		}
	}
	ofPopStyle();
}

//--------------------------------------
ofVec2f DBreeze::getFlow(ofVec2f pos)
{
	return ofVec2f();
}
