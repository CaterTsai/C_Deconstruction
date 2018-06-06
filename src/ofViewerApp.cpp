#include "ofViewerApp.h"


#pragma region Basic
void ofViewerApp::setup()
{
	//Singleton
	displayMgr::GetInstance()->setup("config/_displayConfig.xml");
	postFilter::GetInstance()->init(0, 1920, 1080, true);
	postFilter::GetInstance()->init(1, 300, 300, false);
	postFilter::GetInstance()->init(2, 1024, 1024, false);
	//postFilter::GetInstance()->_squarePost.setFlip(false);
	midiCtrl::GetInstance()->init();
	midiCtrl::GetInstance()->addListener(this);
	
	initVideo();
	initScene();
	_scenceMgr[_nowScence]->start();
	ofSetFrameRate(60);

	_dca.set(1, 1, 14, DCyclicCA::eNeighbouring::eVonNeumann);
	_dca.start();

	_mainTimer = ofGetElapsedTimef();
}

//----------------------------------
void ofViewerApp::update()
{
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	updateMidi();

	camCtrl::GetInstance()->update(delta);
	_scenceMgr[_nowScence]->update(delta);

	_dca.update(delta);

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//----------------------------------
void ofViewerApp::draw()
{
	ofSetBackgroundColor(0);
	_scenceMgr[_nowScence]->draw();

	displayMgr::GetInstance()->displayEachUnit(ofVec2f(0, 500), 200);

	_dca.draw(0, 0, 500, 500);
}

//----------------------------------
void ofViewerApp::keyPressed(int key)
{
	eCtrlType type = ctrlMap::GetInstance()->key2Ctrl[key];
	if (type >= 0 && type < eCtrl_GlobalNum)
	{
		control(type);
	}
	else
	{
		_scenceMgr[_nowScence]->control(type);
	}

	if (key == OF_KEY_BACKSPACE)
	{
		_showMsg ^= true;
	}
}

//----------------------------------
void ofViewerApp::control(eCtrlType ctrl, int value)
{
}

#pragma endregion
//----------------------------------
void ofViewerApp::initScene()
{
	_scenceMgr.push_back(ofPtr<SIdle>(new SIdle()));
	_scenceMgr.push_back(ofPtr<SBIntro>(new SBIntro()));
	_scenceMgr.push_back(ofPtr<SB01>(new SB01()));
	_scenceMgr.push_back(ofPtr<SB02>(new SB02()));
	_scenceMgr.push_back(ofPtr<SB03>(new SB03()));
	_scenceMgr.push_back(ofPtr<SCIntro>(new SCIntro()));
	_scenceMgr.push_back(ofPtr<SC01>(new SC01()));
	_scenceMgr.push_back(ofPtr<SC02>(new SC02()));
	_scenceMgr.push_back(ofPtr<SC03>(new SC03()));
	_scenceMgr.push_back(ofPtr<SC04>(new SC04()));
	_scenceMgr.push_back(ofPtr<SRIntro>(new SRIntro()));
	_scenceMgr.push_back(ofPtr<SR01>(new SR01()));
	_scenceMgr.push_back(ofPtr<SR02>(new SR02()));
	_scenceMgr.push_back(ofPtr<SR03>(new SR03()));
	_scenceMgr.push_back(ofPtr<SR04>(new SR04()));
	_scenceMgr.push_back(ofPtr<SR05>(new SR05()));
	_scenceMgr.push_back(ofPtr<SMIntro>(new SMIntro()));
	_scenceMgr.push_back(ofPtr<SM01>(new SM01()));
	_scenceMgr.push_back(ofPtr<SM02>(new SM02()));
	_scenceMgr.push_back(ofPtr<SM03>(new SM03()));
	_scenceMgr.push_back(ofPtr<SM04>(new SM04()));
	_scenceMgr.push_back(ofPtr<SEncore>(new SEncore()));

	_nowScence = eSIdle;
}

//----------------------------------
void ofViewerApp::initVideo()
{
}

//----------------------------------
void ofViewerApp::updateMidi()
{
	for (int i = 0; i < _midiQueue.size(); i++)
	{
		auto ctrl = _midiQueue.begin();
		if (ctrl->type >= 0 && ctrl->type < eCtrl_GlobalNum)
		{
			control(ctrl->type, ctrl->value);
		}
		else
		{
			_scenceMgr[_nowScence]->control(ctrl->type, ctrl->value);
		}
		_midiQueue.pop_front();
	}
}

//----------------------------------
void ofViewerApp::newMidiMessage(ofxMidiMessage & msg)
{
	midiCtrlData newCtrl;
	newCtrl.type = ctrlMap::GetInstance()->midi2Ctrl[msg.control];
	newCtrl.value = msg.value;
	_midiQueue.push_back(newCtrl);
}

