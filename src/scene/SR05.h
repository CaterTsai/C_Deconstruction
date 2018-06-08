#pragma once

#include "SBase.h"

class SR05 : public SBase {

public:
	SR05()
		:SBase(eSR05)
	{}

	void update(float delta) override
	{
		if (!_isStart)
		{
			return;
		}
		_tail.update(delta);
	}
	void draw() override
	{
		if (!_isStart)
		{
			return;
		}
		displayMgr::GetInstance()->updateOnUnitBegin(eBack);
		postFilter::GetInstance()->_postMgr[eBack].begin();
		_tail.draw();
		postFilter::GetInstance()->_postMgr[eBack].end();
		displayMgr::GetInstance()->updateOnUnitEnd(eBack);
	}
	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "SR05 El desdichardo\n";
		ss << "k1 : Change partical emitter time\n";
		ss << "k2 : Change partical emitter number\n";
		ss << "k3 : Change color\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	}
	void start() override
	{
		_tail.start();

		_rect = displayMgr::GetInstance()->getSize(eBack);
		_isStart = true;
	}
	void stop() override
	{
		_tail.stop();
		_isStart = false;
	}
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override
	{
		switch (ctrl)
		{
		case eCtrlType::eCtrl_ViewKnob1:
		{
			float et = ofMap(cMidiValueMax - value, cMidiValueMin, cMidiValueMax, cTailEmitterTFast, cTailEmitterTSlow);
			_tail.setEmitterT(et);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob2:
		{
			int num = ofMap(value, cMidiValueMin, cMidiValueMax, cTailEmitterNumMin, cTailEmitterNumMax);
			_tail.setEmitterNum(num);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob3:
		{
			int r = ofMap(value, cMidiValueMin, cMidiValueMax, 0, 255);
			_tail.setColor(r);
			break;
		}
		}
	};
	string getSceneName() { return "SR05"; }

private:
	DTail _tail;
	ofRectangle _rect;
};