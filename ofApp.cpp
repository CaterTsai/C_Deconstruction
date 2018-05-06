#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(0);
	_drawImg = false;
	_img.loadImage("img.jpg");

	_voronoi.setup(1024, 1024);
	
	vector<ofVec2f> seedList_;
	for(int idx_ = 0; idx_ < 500; idx_++)
	{
		seedList_.push_back(ofVec2f(rand() % 1024, rand() % 1024));
	}	

	_voronoi.setSeed(seedList_);
}

//--------------------------------------------------------------
void ofApp::update()
{
	_voronoi.begin();
	{
		ofPushStyle();
		ofSetColor(255);
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
		ofRotateZ(ofGetFrameNum() % 360);
		{
			_img.draw(ofGetWidth() * 1.44 * -0.5, ofGetHeight() * 1.44 * -0.5, ofGetWidth() * 1.44, ofGetHeight() * 1.44);
			//_img.draw(ofGetWidth() -0.5, ofGetHeight() * -0.5, ofGetWidth(), ofGetHeight());
		}
		ofPopMatrix();
		ofPopStyle();
	}
	_voronoi.end();
	
	_voronoi.update();
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw()
{
	_voronoi.draw();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}