#include "DStainedGlass.h"

//-----------------------------------------
void DStainedGlass::update(float delta)
{
	CHECK_START();

	_voronoi.begin();
	{
		ofPushStyle();
		ofSetColor(255);
		ofPushMatrix();
		{
			_img.draw(0, 0);
		}
		ofPopMatrix();
		ofPopStyle();
	}
	_voronoi.end();
	_voronoi.update();
}

//-----------------------------------------
void DStainedGlass::draw()
{
	_voronoi.draw();
}

//-----------------------------------------
void DStainedGlass::start()
{
	initVoronoi();
	_isStart = true;
}

//-----------------------------------------
void DStainedGlass::stop()
{
	_isStart = false;
}

//-----------------------------------------
void DStainedGlass::trigger(int key)
{
}

//-----------------------------------------
void DStainedGlass::initVoronoi()
{
	_voronoi.setup(1024, 1024);
	vector<ofVec2f> seedList_;
	for (int idx_ = 0; idx_ < 5000; idx_++)
	{
		seedList_.push_back(ofVec2f(rand() % 1024, rand() % 1024));
	}
	
	_voronoi.setSeed(seedList_);
}
