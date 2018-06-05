#pragma once

#include "SBase.h"

class SC03 : public SBase {

public:
	SC03()
		:SBase(eSC03)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SC03"; }

private:

};