#pragma once

#include "SBase.h"

class SC02 : public SBase {

public:
	SC02()
		:SBase(eSC02)
	{}

	void update(float delta) override
	{
		if (!_isStart)
		{
			return;
		}
		_di.update(delta);
	}

	void draw() override
	{
		if (!_isStart)
		{
			return;
		}
		displayMgr::GetInstance()->updateOnUnitBegin(eFront);
		_di.draw(100, 0);
		displayMgr::GetInstance()->updateOnUnitEnd(eFront);

	};

	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "SC02 Ah! guarda sorella\n";
		ss << "1:Next Photo User 1\n";
		ss << "2:Next Photo User 2\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};


	void start() override
	{
		_isStart = true;
		_di.start();
	};
	void stop() override
	{
		_isStart = false;
		_di.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override
	{
		if (value == cMidiButtonPress)
		{
			switch (ctrl)
			{
			case eCtrlType::eCtrl_ViewTrigger1:
			{
				_di.trigger(0);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger2:
			{
				_di.trigger(1);
				break;
			}
			}
		}
	};


	string getSceneName() { return "SC02"; }

private:
	DInstagram _di;
};