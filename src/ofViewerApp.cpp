#include "ofViewerApp.h"


#pragma region Basic
void ofViewerApp::setup()
{

	//Singleton
	displayMgr::GetInstance()->setup("config/_displayConfig.xml");
	//postFilter::GetInstance()->init(200, 200, cViewCanvasWidth, cViewCanvasWidth);
	//postFilter::GetInstance()->_squarePost.setFlip(false);
	//midiCtrl::GetInstance()->init();
	//midiCtrl::GetInstance()->addListener(this);
	ofSetFrameRate(60);

	_mainTimer = ofGetElapsedTimef();
}

void ofViewerApp::update()
{
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

void ofViewerApp::draw()
{
}

void ofViewerApp::keyPressed(int key)
{
}

void ofViewerApp::mouseDragged(int x, int y, int button)
{
}
#pragma endregion


