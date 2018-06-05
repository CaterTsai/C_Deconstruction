#pragma once

#include "SBase.h"

class SIdle : public SBase {

public:
	SIdle()
		:SBase(eSIdle)
	{}

	void update(float delta) override {}
	void draw() override 
	{
		displayMgr::GetInstance()->updateOnUnitBegin(eFront);
		camCtrl::GetInstance()->getCanvasCam().begin();
		ofSetColor(255, 0, 0);
		ofDrawCircle(0, 0, 100);
		camCtrl::GetInstance()->getCanvasCam().end();
		displayMgr::GetInstance()->updateOnUnitEnd(eFront);

	};
	void drawMsg(ofVec2f pos) override {};
	void start() override 
	{
		camCtrl::GetInstance()->_canvasCam.reset();
	};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SIdle"; }

private:

};