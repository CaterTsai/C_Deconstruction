#pragma once

#include "SBase.h"

class SC04 : public SBase {

public:
	SC04()
		:SBase(eSC04)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SC04"; }

private:

};