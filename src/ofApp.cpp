#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(255);
	ofSetFrameRate(60);

	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update() {
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw() {


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
}
