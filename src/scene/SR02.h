#pragma once

#include "SBase.h"

class SR02 : public SBase {

public:
	SR02()
		:SBase(eSR02)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SR02"; }

private:
	
};