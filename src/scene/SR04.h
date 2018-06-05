#pragma once

#include "SBase.h"

class SR04 : public SBase {

public:
	SR04()
		:SBase(eSR04)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SR04"; }

private:

};