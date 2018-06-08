#pragma once

#include "SBase.h"
#include "ofxLayerMask.h"

class SB03 : public SBase {

public:
	SB03()
		:SBase(eSB03)
	{
		_colorBase.set(0, 72, 93);
	}

	void update(float delta) override
	{
		if (!_isStart)
		{
			return;
		}
		_dev.update(delta);
		_layer.beginLayer();
		{
			ofPushStyle();
			ofBackgroundGradient(_displayRect.getWidth(), _displayRect.getHeight(), _color1, _color2, OF_GRADIENT_LINEAR);
			ofPopStyle();
		}
		_layer.endLayer();

		_layer.beginMask();
		{
			ofPushStyle();
			ofClear(0);
			ofSetColor(ofColor::white);
			_dev.draw();
			ofPopStyle();
		}
		_layer.endMask();
	}

	void draw() override
	{
		if (!_isStart)
		{
			return;
		}
		displayMgr::GetInstance()->updateOnUnitBegin(eFront, true);
		postFilter::GetInstance()->_postMgr[eFront].begin();
		_layer.draw();
		postFilter::GetInstance()->_postMgr[eFront].end();
		displayMgr::GetInstance()->updateOnUnitEnd(eFront);
	}

	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "SB03 Piangero la Sorte mia\n";
		ss << "1-10 : Troggle Cirlce\n";
		ss << "k1-2 : Change Color";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	void start() override
	{
		_color1 = _color2 = _colorBase;
		
		_displayRect = displayMgr::GetInstance()->getSize(eFront);
		_layer.setup(_displayRect.width, _displayRect.width);
		_layer.newLayer();

		_dev.start();
		_isStart = true;
	}

	void stop() override
	{
		_dev.stop();
		_isStart = false;
	}

	void control(eCtrlType ctrl, int value = cMidiButtonPress) override
	{
		if (value == cMidiButtonPress)
		{
			switch (ctrl)
			{
			case eCtrlType::eCtrl_ViewTrigger1:
			{
				_dev.trigger(0);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger2:
			{
				_dev.trigger(1);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger3:
			{
				_dev.trigger(2);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger4:
			{
				_dev.trigger(3);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger5:
			{
				_dev.trigger(4);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger6:
			{
				_dev.trigger(5);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger7:
			{
				_dev.trigger(6);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger8:
			{
				_dev.trigger(7);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger9:
			{
				_dev.trigger(8);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger10:
			{
				_dev.trigger(9);
				break;
			}
			}
		}

		switch (ctrl)
		{
		case eCtrlType::eCtrl_ViewKnob1: {
			_color1.r = ofMap(value, cMidiValueMin, cMidiValueMax, 0, 255);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob2: {
			_color2.r = ofMap(value, cMidiValueMin, cMidiValueMax, 0, 255);
			break;
		}
		}

	};
	string getSceneName() { return "SB03"; }

private:
	DEgyptianVertical _dev;
	ofRectangle _displayRect;
	ofxLayerMask _layer;

	ofColor _color1, _color2;
	ofColor _colorBase;
};