#pragma once

#include "SBase.h"

class SC04 : public SBase {

public:
	SC04()
		:SBase(eSC04)
	{}

	void update(float delta) override
	{
		_dt.update(delta);
	}

	void draw() override
	{
		displayMgr::GetInstance()->updateOnUnitBegin(eFront, true);
		postFilter::GetInstance()->_postMgr[eFront].begin(camCtrl::GetInstance()->getCanvasCam());

		_dt.draw();
		postFilter::GetInstance()->_postMgr[eFront].end();
		displayMgr::GetInstance()->updateOnUnitEnd(eFront);
	}

	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "SB04 Del fiero duol che il cor mi frange\n";
		ss << "1-7 : Troggle Light\n";
		ss << "k1 : Change light color\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	void start() override {
		_dt.start();
		camCtrl::GetInstance()->getCanvasCam().setFarClip(2000);
		camCtrl::GetInstance()->_canvasCam.setFixed(ofVec3f(0, -300, 700));
		camCtrl::GetInstance()->_canvasCam.setTarget(ofVec3f(0, -300, 0));
	};

	void stop() override {
		_dt.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override
	{
		switch (ctrl)
		{
		case eCtrlType::eCtrl_ViewTrigger1:
		{
			_dt.trigger(0);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger2:
		{
			_dt.trigger(1);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger3:
		{
			_dt.trigger(2);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger4:
		{
			_dt.trigger(3);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger5:
		{
			_dt.trigger(4);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger6:
		{
			_dt.trigger(5);
			break;
		}
		case eCtrlType::eCtrl_ViewTrigger7:
		{
			_dt.trigger(6);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob1: 
		{
			int g = ofMap(value, cMidiValueMin, cMidiValueMax, 0, 255);
			_dt.setColorG(g);
		}
		}
	};
	string getSceneName() { return "SC04"; }

private:
	DTemple _dt;

};