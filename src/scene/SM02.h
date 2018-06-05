#pragma once

#include "SBase.h"

class SM02 : public SBase {

public:
	SM02()
		:SBase(eSM02)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SM02"; }

private:

};