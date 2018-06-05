#pragma once

#include "SBase.h"

class SC01 : public SBase {

public:
	SC01()
		:SBase(eSC01)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SC01"; }

private:

};