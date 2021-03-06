#pragma once

#include "SBase.h"

class SBIntro : public SBase {

public:
	SBIntro()
		:SBase(eSBIntro)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "Baroque Intro\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SBIntro"; }

private:

};