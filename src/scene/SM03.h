#pragma once

#include "SBase.h"

class SM03 : public SBase {

public:
	SM03()
		:SBase(eSM03)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SM03"; }

private:

};