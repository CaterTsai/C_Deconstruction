#pragma once

#include "SBase.h"

class SM02 : public SBase {

public:
	SM02()
		:SBase(eSM02)
	{
		_back.load("images/tree_bg.png");
		_front.load("images/tree_front.png");
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
		//_front.draw(_rect);
		ofPopStyle();
		displayMgr::GetInstance()->updateOnUnitEnd(eBack);
	};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "SM02 The Trees on the Mountain\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void start() override
	{
		auto displayRect = displayMgr::GetInstance()->getSize(eBack);
		_rect.width = displayRect.width;
		_rect.height = displayRect.width * (_back.getHeight() /_back.getWidth());
		_rect.x = 0;
		_rect.y = (displayRect.height - _rect.height) * 0.5;

		_dccaRect.set(869, 480, 1000, 450);
		_dccaRect.scale(displayRect.width / _back.getWidth());
		_dccaRect.x *= displayRect.width / _back.getWidth();

		_dccaRect.y *= displayRect.width / _back.getWidth();
		_dccaRect.y += _dccaRect.getY();

		_dcca.set(2, 3, 5, DCyclicCA::eNeighbouring::eVonNeumann);
		_dcca.setBaseColor(ofColor(107, 0, 200));
		_dcca.start();

		_isStart = true;
	};

	void stop() override 
	{
		_dcca.stop();
		_isStart = false;
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SM02"; }

private:
	ofRectangle _rect, _dccaRect;
	DCyclicCA _dcca;
	ofImage _back, _front;
};