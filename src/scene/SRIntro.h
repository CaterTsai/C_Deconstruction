#pragma once

#include "SBase.h"

class SRIntro : public SBase {

public:
	SRIntro()
		:SBase(eSRIntro)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "Roman Intro\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SRIntro"; }

private:

};