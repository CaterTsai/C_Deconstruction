#pragma once

#include "SBase.h"

class SIdle : public SBase {

public:
	SIdle()
		:SBase(eSIdle)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "SIdel";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void start() override 
	{
	};
	void stop() override 
	{
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SIdle"; }

private:

};