#pragma once

#include "SBase.h"

class SEncore : public SBase {

public:
	SEncore()
		:SBase(eSEncore)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "SEncore";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SEncore"; }

private:

};