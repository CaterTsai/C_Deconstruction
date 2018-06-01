#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);
	//_post.init(1024, 1024);
	//_post.createPass<BloomPass>()->setEnabled(true);

	
	//_drc.start();
	//_dsg.start();
	//_dev.start();
	//_dbr.start();
	//_dtp.start();
	_dpt.start();
	_cam.setVFlip(true);
	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update() {
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	//_drc.update(delta);
	//_dsg.update(delta);
	//_dev.update(delta);
	//_dbr.update(delta);
	//_dtp.update(delta);
	_dpt.update(delta);

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw() {
	//_cam.begin();
	//_drc.draw();
	//_dtp.draw();
	//_cam.end();

	//_dev.draw();
	//_dbr.draw();
	_dpt.draw();
	//_post.begin(_cam);
	//_dsg.draw();
	//_post.end();

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
		//_drc.trigger(key - '0');
		//_dev.trigger(key - '0');
		//_dtp.trigger(key - '0');
		break;
	}

	case ' ':
	{
		//_dsg.startRotate(5.0f);
		//_dbr.trigger(key);
		//_dtp.trigger(key);
		break;
	}
	}
}
