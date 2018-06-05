#pragma once

#include "SBase.h"

class SB03 : public SBase {

public:
	SB03()
		:SBase(eSB03)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SB03"; }

private:

};