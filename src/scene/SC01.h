#pragma once

#include "SBase.h"

class SC01 : public SBase {

public:
	SC01()
		:SBase(eSC01)
	{}

	void update(float delta) override 
	{
		if (!_isStart)
		{
			return;
		}
		_db.update(delta);
	}

	void draw() override 
	{
		if (!_isStart)
		{
			return;
		}
		displayMgr::GetInstance()->updateOnUnitBegin(eFront, true);
		postFilter::GetInstance()->_postMgr[eFront].begin();
		_db.draw();
		postFilter::GetInstance()->_postMgr[eFront].end();
		displayMgr::GetInstance()->updateOnUnitEnd(eFront);
	
	}

	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "SC01 Sullaria\n";
		ss << "1 : Troggle AutoEmitter\n";
		ss << "2-4 : Change Random Type\n";
		ss << "k1 : Change emitter time\n";
		ss << "k2 : Change emitter num\n";
		ss << "k3 : Change color\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	void start() override 
	{
		_isStart = true;
		_db.start();
	}

	void stop() override 
	{
		_isStart = false;
		_db.stop();
	}

	void control(eCtrlType ctrl, int value = cMidiButtonPress) 
	{
		if (value == cMidiButtonPress)
		{
			switch (ctrl)
			{
			case eCtrlType::eCtrl_ViewTrigger1:
			{
				_db.toggleAutoEmitter();
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger2:
			{
				_db.setEmitter(DBreeze::ePType2DRandom);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger3:
			{
				_db.setEmitter(DBreeze::ePType3DRandom);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger4:
			{
				_db.setEmitter(DBreeze::ePTypeRandom);
				break;
			}
			case eCtrlType::eCtrl_ViewTrigger5: {
				_db.setEmitterT(2.0f);
				break;
			}
			}
		}
		
		switch(ctrl)
		{
		case eCtrlType::eCtrl_ViewKnob1:
		{
			float et = ofMap(cMidiValueMax - value, cMidiValueMin, cMidiValueMax, cBreezEmitterFast, cBreezEmitterSlow);
			_db.setEmitterT(et);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob2:
		{
			int num = ofMap(value, cMidiValueMin, cMidiValueMax, cBreezEmitterNumMin, cBreezEmitterNumMax);
			_db.setEmitterNum(num);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob3:
		{
			int r = ofMap(value, cMidiValueMin, cMidiValueMax, 0, 255);
			_db.setColorR(r);
			break;
		}
		}
	};
	string getSceneName() { return "SC01"; }

private:
	DBreeze _db;
};