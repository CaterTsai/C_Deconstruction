#pragma once

#include "SBase.h"

class SR01 : public SBase {

public:
	SR01()
		:SBase(eSR01)
	{}

	void update(float delta) override 
	{
		if (!_isStart)
		{
			return;
		}
		_dp.update(delta);
	}

	void draw() override 
	{
		if (!_isStart)
		{
			return;
		}
		displayMgr::GetInstance()->updateOnUnitBegin(eObject, true);
		postFilter::GetInstance()->_postMgr[eObject].begin();
		
		_dp.draw(0, 0, _displayRect.getWidth(), _displayRect.getHeight());
		_dp.drawPhoto(_displayRect.getWidth(), _displayRect.getHeight());
		postFilter::GetInstance()->_postMgr[eObject].end();
		displayMgr::GetInstance()->updateOnUnitEnd(eObject);
	};

	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "SR01 & SR02 Schelm, half fest\n";
		ss << "1:Cross Photo\n";
		ss << "2:Weber, 3:Tiny, 4:Maki\n";
		ss << "5:Circle, 6:Center\n";
		ss << "7-9:Mask\n";
		ss << "k1 : Rotate V\n";
		ss << "k2 : Change Color\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void start() override 
	{
		_displayRect = displayMgr::GetInstance()->getSize(eObject);
		_dp.start();
		_isStart = true;

	};
	void stop() override 
	{
		_dp.stop();
		_isStart = false;

	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{
		if (value == cMidiButtonPress)
		{
			switch (ctrl)
			{
			case eCtrlType::eCtrl_ViewTrigger1:
			{
				_dp.togglePhoto();
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger2:
			{
				_dp.trigger(0);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger3:
			{
				_dp.trigger(1);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger4:
			{
				_dp.trigger(2);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger5:
			{
				_dp.trigger(3);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger6:
			{
				_dp.trigger(4);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger7:
			{
				_dp.trigger(5);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger8:
			{
				_dp.trigger(6);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger9:
			{
				_dp.trigger(7);
				break;
			}
			}
		}
		
		switch(ctrl)
		{
		case eCtrlType::eCtrl_ViewKnob1:
		{
			_dp.setRotateV(ofMap(value, cMidiValueMin, cMidiValueMax, 0.0f, 180.0f));
			break;
		}
		case eCtrlType::eCtrl_ViewKnob2:
		{
			_dp.setColorR(ofMap(value, cMidiValueMin, cMidiValueMax, 0.0f, 255.0f));
			break;
		}
		}
	};
	string getSceneName() { return "SR01"; }

private:
	ofRectangle _displayRect;
	DPortrait _dp;
};