#pragma once

#include "constParameter.h"
#include "displayMgr.h"
#include "camCtrl.h"
#include "postFilter.h"
#include "videoMgr.h"
#include "midiCtrl.h"

#include "sceneMgr.h"

class ofViewerApp : public ofBaseApp, public ofxMidiListener {

public:
	ofViewerApp()
	{
	}

	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void control(eCtrlType ctrl, int value = cMidiButtonPress);
private:
	bool _showMsg;
	float _mainTimer;

	//Scence
private:
	void initScene();
private:
	bool _isStart;
	vector<ofPtr<SBase>> _scenceMgr;
	eSType	_nowScence;

	//PostFilter
	bool _targetSquare;

	//Video
public:
	void initVideo();

	//Midi
public:
	void updateMidi();
	void newMidiMessage(ofxMidiMessage& msg) override;

private:
	struct midiCtrlData
	{
		eCtrlType type;
		int value;
	};
	list<midiCtrlData> _midiQueue;

};
