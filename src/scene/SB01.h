#pragma once

#include "SBase.h"
#include "ofxLayerMask.h"

class SB01 : public SBase {

public:
	SB01()
		:SBase(eSB01)
	{
		_colorBase.set(0, 152, 188);
	}

	void update(float delta) override
	{
		if (!_isStart)
		{
			return;
		}
		_drc.update(delta);

		_layer.beginLayer();
		{
			ofPushStyle();
			//ofBackground(ofColor(255, 0, 0));
			ofBackgroundGradient(_displayRect.width, _displayRect.height, _color1, _color2, OF_GRADIENT_LINEAR);
			ofPopStyle();
		}
		_layer.endLayer();

		_layer.beginMask();
		{
			
			ofPushStyle();
			ofClear(0);
			ofSetColor(ofColor::white);
			ofPushMatrix();
			ofTranslate(_displayRect.width * 0.5, _displayRect.height * 0.5);
			_drc.draw();
			ofPopMatrix();
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


	};
	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "SB01 Pur ti miro\n";
		ss << "1-7 : Troggle Cirlce\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void start() override
	{
		_displayRect = displayMgr::GetInstance()->getSize(eFront);
		_layer.setup(_displayRect.width, _displayRect.height);
		_layer.newLayer();

		_drc.start();
		_color1 = _color2 = _colorBase;
		_isStart = true;
	};
	void stop() override
	{
		_drc.stop();

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
				_drc.trigger(0);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger2:
			{
				_drc.trigger(1);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger3:
			{
				_drc.trigger(2);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger4:
			{
				_drc.trigger(3);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger5:
			{
				_drc.trigger(4);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger6:
			{
				_drc.trigger(5);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger7:
			{
				_drc.trigger(6);
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
	string getSceneName() { return "SB01"; }

private:
	ofColor _colorBase;
	ofColor _color1, _color2;
	DRomanCircle _drc;
	ofxLayerMask _layer;
	ofRectangle _displayRect;
};