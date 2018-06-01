#include "DPortrait.h"

#pragma region pUnit

#pragma endregion
//-----------------------------------
void DPortrait::update(float delta)
{
	CHECK_START();
}

//-----------------------------------
void DPortrait::draw()
{
	CHECK_START();

	ofPushStyle();
	ofSetColor(255);
	_weber.photo.draw(0, 0);
	for (int i = 0; i < _weber.size; i++)
	{	
		//ofSetColor(_weber.color[i]);
		ofSetColor(255);
		ofDrawCircle(_weber.pos[i], 2);
	}

	ofPopStyle();
}

//-----------------------------------
void DPortrait::start()
{
	_isStart = true;
}

//-----------------------------------
void DPortrait::stop()
{
	_isStart = false;
}

//-----------------------------------
void DPortrait::trigger(int key)
{
}

//-----------------------------------
void DPortrait::loadPortrait()
{
	ofImage weber, weberMask;
	weber.loadImage("portrait/weber_photo.jpg");
	weberMask.loadImage("portrait/weber_mask.jpg");

	ofPixels maskP = weberMask.getPixelsRef();
	ofPixels photoP = weber.getPixelsRef();

	vector<ofVec2f> pList;
	for (int x = 0; x < weberMask.getWidth(); x++)
	{
		for (int y = 0; y < weberMask.getHeight(); y++)
		{
			int index = (y * weberMask.getWidth() + x) * 3;
			if ((maskP[index] + maskP[index + 1] + maskP[index + 2]) > cPortraitMaskThreshold)
			{
				pList.push_back(ofVec2f(x, y));
			}
		}
	}

	int interval = (int)ceil(pList.size() / (float)cPortraitUnitSize);

	if (interval >= 1)
	{
		int index = 0;
		for (int i = 0; i < pList.size(); i += interval, index++)
		{
			//_weber.pos[index] = pList[i];
			
			auto p = pList[i] * cPortraitMaskToPhoto;
			int photoIdx = (p.y * weber.getWidth() + p.x) * 3;
			_weber.color[index].r = photoP[photoIdx];
			_weber.color[index].g = photoP[photoIdx + 1];
			_weber.color[index].b = photoP[photoIdx + 2];

			_weber.pos[index] = p;
		}
		_weber.photo = weber;
		_weber.size = index;
	}
}
