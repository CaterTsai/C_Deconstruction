#pragma once

#include "SBase.h"

class SB02 : public SBase {

public:
	SB02()
		:SBase(eSB02)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SB02"; }

private:

};