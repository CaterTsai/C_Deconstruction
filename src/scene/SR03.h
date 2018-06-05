#pragma once

#include "SBase.h"

class SR03 : public SBase {

public:
	SR03()
		:SBase(eSR03)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SR03"; }

private:

};