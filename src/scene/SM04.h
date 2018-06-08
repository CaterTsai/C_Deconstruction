#pragma once

#include "SBase.h"

class SM04 : public SBase {

public:
	SM04()
		:SBase(eSM04)
	{
		_back.load("images/tear_bg.png");
		_front.load("images/tear_front.png");
	}

	void update(float delta) override
	{
		if (!_isStart)
		{
			return;
		}
		_dcca.update(delta);
	}

	void draw() override
	{
		if (!_isStart)
		{
			return;
		}
		displayMgr::GetInstance()->updateOnUnitBegin(eBack);
		ofPushStyle();

		postFilter::GetInstance()->_postMgr[eBack].begin();
		_dcca.draw(_dccaRect.x, _dccaRect.y, _dccaRect.width, _dccaRect.height);
		postFilter::GetInstance()->_postMgr[eBack].end();

		ofSetColor(255);
		_back.draw(_rect);
		_front.draw(_rect);
		ofPopStyle();
		displayMgr::GetInstance()->updateOnUnitEnd(eBack);
	};
	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "SM04 Nami\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};

	void start() override
	{
		auto displayRect = displayMgr::GetInstance()->getSize(eBack);
		_rect.height = displayRect.height;
		_rect.width = displayRect.width * (_back.getWidth() / _back.getHeight());
		_rect.x = (displayRect.width - _rect.width) * 0.5;
		_rect.y = 0;

		_dccaRect.set(111, 395, 735, 1122);
		_dccaRect.scale(displayRect.height / _back.getHeight());
		_dccaRect.x *= displayRect.height / _back.getHeight();
		_dccaRect.x += _rect.x;

		_dccaRect.y *= displayRect.height / _back.getHeight();

		_dcca.start();
		_isStart = true;

	};
	void stop() override
	{
		_dcca.stop();
		_isStart = false;
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SM04"; }

private:
	ofRectangle _rect, _dccaRect;
	DCyclicCA _dcca;
	ofImage _back, _front;
};