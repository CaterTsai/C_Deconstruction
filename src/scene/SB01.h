#pragma once

#include "SBase.h"

class SB01 : public SBase {

public:
	SB01()
		:SBase(eSB01)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SB01"; }

private:

};