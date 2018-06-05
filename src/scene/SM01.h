#pragma once

#include "SBase.h"

class SM01 : public SBase {

public:
	SM01()
		:SBase(eSM01)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SM01"; }

private:

};