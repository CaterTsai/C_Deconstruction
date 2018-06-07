#pragma once

#include "SBase.h"

class SB02 : public SBase {

public:
	SB02()
		:SBase(eSB02)
	{}

	void update(float delta) override 
	{
		_dsg.update(delta);
	}

	void draw() override 
	{
		displayMgr::GetInstance()->updateOnUnitBegin(eFront, true);
		postFilter::GetInstance()->_postMgr[eFront].begin();
		_dsg.draw(cSB02_Pos.x, cSB02_Pos.y);
		postFilter::GetInstance()->_postMgr[eFront].end();
		displayMgr::GetInstance()->updateOnUnitEnd(eFront);
	}
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "SB02 Alma oppressa\n";
		ss << "1-8 : Change Glass\n";
		ss << "k1 : Change RV\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void start() override 
	{
		_dsg.start();
	}

	void stop() override 
	{
		_dsg.stop();
	}
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override
	{
		switch (ctrl)
		{
		case eCtrlType::eCtrl_ViewTrigger1:
		{
			_dsg.trigger(0);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger2:
		{
			_dsg.trigger(1);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger3:
		{
			_dsg.trigger(2);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger4:
		{
			_dsg.trigger(3);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger5:
		{
			_dsg.trigger(4);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger6:
		{
			_dsg.trigger(5);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger7:
		{
			_dsg.trigger(6);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger8:
		{
			_dsg.trigger(7);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob1:
		{
			float rv = ofMap(value, cMidiValueMin, cMidiValueMax, cStainedRotateMin, cStainedRotateMax);
			_dsg.setRotateV(rv);
			break;
		}
		}
	};
	string getSceneName() { return "SB02"; }

private:
	DStainedGlass _dsg;
};