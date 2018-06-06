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
		ofPushStyle();
		ofSetColor(255, 0, 0);
		ofDrawRectangle(0, 0, _displayRect.width, _displayRect.height);
		ofPopStyle();
		_layer.endLayer();

		_layer.beginMask();
		ofPushStyle();
		ofClear(0);
		ofSetColor(ofColor::white);
		ofDrawRectangle(0, 0, _displayRect.width, _displayRect.height);

		/*ofClear(0);
		ofPushMatrix();
		ofTranslate(_displayRect.width * 0.5, _displayRect.height * 0.5);
		_drc.draw();
		ofPopMatrix();*/
		ofPopStyle();
		_layer.endMask();
		
	}

	void draw() override 
	{
		_layer.draw(100, 100);
		/*displayMgr::GetInstance()->updateOnUnitBegin(eFront, true);
		_layer.draw();
		displayMgr::GetInstance()->updateOnUnitEnd(eFront);
		*/
	};
	void drawMsg(ofVec2f pos) override {};
	void start() override 
	{
		camCtrl::GetInstance()->reset();
		_displayRect = displayMgr::GetInstance()->getSize(eFront);
		_layer.setup(_displayRect.width, _displayRect.width);
		_layer.newLayer();

		//_drc.start();
		_drc.trigger(0);
		_drc.trigger(1);
		_drc.trigger(2);
	};
	void stop() override 
	{
		_drc.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SB01"; }

private:
	DRomanCircle _drc;
	ofxLayerMask _layer;
	ofRectangle _displayRect;
};