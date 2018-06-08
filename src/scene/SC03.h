#pragma once

#include "SBase.h"

class SC03 : public SBase {

public:
	SC03()
		:SBase(eSC03)
	{}

	void update(float delta) override 
	{
		_dc.update(delta);
	}

	void draw() override 
	{
		displayMgr::GetInstance()->updateOnUnitBegin(eFront, true);
		postFilter::GetInstance()->_postMgr[eFront].begin();
		_dc.draw();
		postFilter::GetInstance()->_postMgr[eFront].end();
		displayMgr::GetInstance()->updateOnUnitEnd(eFront);

	}
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "SC03 Fra un dolce delirio\n";
		ss << "k1 : Change partical emitter time\n";
		ss << "k2 : Change cloud emitter time\n";
		ss << "k3 : Change color\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void start() override 
	{
		_dc.start();
	}

	void stop() override 
	{
		_dc.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{
		switch (ctrl)
		{
		case eCtrlType::eCtrl_ViewKnob1:
		{
			float et = ofMap(value, cMidiValueMin, cMidiValueMax, cCloudPEmitterFast, cCloudPEmitterSlow);
			_dc.setPEmmiterT(et);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob2:
		{
			int num = ofMap(value, cMidiValueMin, cMidiValueMax, cCloudCEmitterFast, cCloudCEmitterSlow);
			_dc.setCEmmiterT(num);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob3:
		{
			int r = ofMap(value, cMidiValueMin, cMidiValueMax, 0, 255);
			_dc.setColorR(r);
			break;
		}
		}
	};
	string getSceneName() { return "SC03"; }

private:
	DClouds _dc;
};