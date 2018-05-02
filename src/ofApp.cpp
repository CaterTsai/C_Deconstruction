#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);

	_drc.start();
	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update() {
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	_drc.update(delta);
}

//--------------------------------------------------------------
void ofApp::draw() {
	_cam.begin();
	_drc.draw();
	_cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		_drc.trigger(key - '0');
		break;
	}
	}
}
