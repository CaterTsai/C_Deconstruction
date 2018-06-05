#pragma once

#include "SBase.h"

class SCIntro : public SBase {

public:
	SCIntro()
		:SBase(eSCIntro)
	{}

	void update(float delta) override {}
	void draw() override {};
	void drawMsg(ofVec2f pos) override {};
	void start() override {};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SCIntro"; }

private:

};