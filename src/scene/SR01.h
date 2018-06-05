#pragma once

#include "SBase.h"

class SR01 : public SBase {

public:
	SR01()
		:SBase(eSR01)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SR01"; }

private:

};