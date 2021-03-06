#pragma once

#include "SBase.h"

class SMIntro : public SBase {

public:
	SMIntro()
		:SBase(eSMIntro)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "Modern Intro\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SMIntro"; }

private:

};