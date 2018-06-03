#include "DClouds.h"

#pragma region cloudUnit
//---------------------------------
void DClouds::cloudUnit::update(float delta)
{
}

//---------------------------------
void DClouds::cloudUnit::set(int cloudIndex)
{
	_eType = eCloudImg;
	_cloudIdx = cloudIndex;


}

//---------------------------------
void DClouds::cloudUnit::set(ofColor color)
{
}

//---------------------------------
void DClouds::cloudUnit::init()
{
	int x = 0;
	if (rand() % 2 == 0)
	{
		x = ofGetWidth() +  ofRandom()
	}
	_source.set()
	_anim = 0.0f;
	_animV = 1.0f / ofRandom(15, 30);
}
#pragma endregion

//---------------------------------
void DClouds::update(float delta)
{
	CHECK_START();
}

//---------------------------------
void DClouds::draw()
{
	CHECK_START();
}

//---------------------------------
void DClouds::start()
{
	_isStart = true;
}

//---------------------------------
void DClouds::stop()
{
	_isStart = false;
}

//---------------------------------
void DClouds::trigger(int key)
{
}

//---------------------------------
void DClouds::loadClouds()
{
	for (int i = 0; i < cCloudImgNum; i++)
	{
		_cloudsImg[i].load("clouds/cloud_" + ofToString(i + 1) + ".png");
	}
}

//---------------------------------
void DClouds::addPartical()
{
}

//---------------------------------
void DClouds::addCloudUnit()
{
}
