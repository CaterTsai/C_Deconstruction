#pragma once

#include "SBase.h"

class SM04 : public SBase {

public:
	SM04()
		:SBase(eSM04)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SM04"; }

private:

};