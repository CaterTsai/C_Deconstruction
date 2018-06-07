#pragma once

#include "SBase.h"
#include "ofxLayerMask.h"

class SB01 : public SBase {

public:
	SB01()
		:SBase(eSB01)
	{}

	void update(float delta) override 
	{
		_drc.update(delta);

		_layer.beginLayer();
		{
			ofPushStyle();
			ofSetColor(255, 0, 0);
			ofDrawRectangle(0, 0, _displayRect.width, _displayRect.height);
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
		camCtrl::GetInstance()->reset();
		_displayRect = displayMgr::GetInstance()->getSize(eFront);
		_layer.setup(_displayRect.width, _displayRect.width);
		_layer.newLayer();

		_drc.start();
	};
	void stop() override 
	{
		_drc.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
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
	};
	string getSceneName() { return "SB01"; }

private:
	DRomanCircle _drc;
	ofxLayerMask _layer;
	ofRectangle _displayRect;
};