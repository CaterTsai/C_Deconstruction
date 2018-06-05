#pragma once

#include "SBase.h"

class SC02 : public SBase {

public:
	SC02()
		:SBase(eSC02)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SC02"; }

private:

};