#pragma once

#include "SBase.h"

class SR05 : public SBase {

public:
	SR05()
		:SBase(eSR05)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SR05"; }

private:

};