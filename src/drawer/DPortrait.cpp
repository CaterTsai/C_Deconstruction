#include "DPortrait.h"

#pragma region pUnit
//-----------------------------------
void DPortrait::pUnit::update(float delta)
{
	_animC.update(delta);
	_animPos.update(delta);

	_offset += _offsetV * delta;
	if (_offset.distance(ofVec2f(0, 0)) < 3.0f)
	{
		_offset.set(0);
		_offsetV.set(0);
	}
}

//-----------------------------------
void DPortrait::pUnit::setMove(ofVec2f pos, float duration)
{
	_offset = pos - _animPos.getCurrentPosition();
	_offsetV = (_animPos.getCurrentPosition() - pos) / duration;
}

#pragma endregion

//-----------------------------------
void DPortrait::update(float delta)
{
	CHECK_START();

	_animAlpha.update(delta);
	for (auto& iter : _pList) {
		iter.update(delta);
	}
}

//-----------------------------------
void DPortrait::draw()
{
	CHECK_START();

	ofPushStyle();
	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(1024 * 0.5, 1024 * 0.5);
	for (auto& iter : _pList) {
		ofSetColor(iter._animC.getCurrentColor(), _animAlpha.getCurrentValue());
		ofVec2f pos = iter._animPos.getCurrentPosition() + iter._offset;
		ofDrawCircle(pos, 5);
	}
	ofPopMatrix();
	ofPopStyle();
}

//-----------------------------------
void DPortrait::drawPhoto()
{
	CHECK_START();

	ofPushStyle();
	ofSetColor(255, 255.0f - _animAlpha.getCurrentValue());
	ofPushMatrix();
	ofTranslate(1024 * 0.5, 1024 * 0.5);
	switch (_eState)
	{
	case eWeber:
	{
		_weber.photo.draw(_weber.photo.getWidth() * -0.5, _weber.photo.getHeight() * -0.5);
		break;
	}
	case eTiny:
	{
		_tiny.photo.draw(_tiny.photo.getWidth() * -0.5, _tiny.photo.getHeight() * -0.5);
		break;
	}
	case eMaki:
	{
		_maki.photo.draw(_maki.photo.getWidth() * -0.5, _maki.photo.getHeight() * -0.5);
		break;
	}
	}
	ofPopMatrix();
	ofPopStyle();

}

//-----------------------------------
void DPortrait::start()
{
	initPartical();
	toPortrait(1.0f, _weber);
	_animAlpha.reset(0.0);
	_isStart = true;
	_eState = eWeber;
}

//-----------------------------------
void DPortrait::stop()
{
	_isStart = false;
}

//-----------------------------------
void DPortrait::trigger(int key)
{
	switch (key)
	{
	case 0:
	{
		toCircle(3.0f);
		_eState = eCircle;
		toColor(3.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
		break;
	}
	case 1: {
		toCenter(3.0f);
		_eState = eCenter;
		toColor(3.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
		break;
	}
	case 2: {
		_eState = eWeber;
		toPortrait(3.0f, _weber);
		break;
	}
	case 3: {
		_eState = eTiny;
		toPortrait(3.0f, _tiny);
		break;
	}
	case 4: {
		_eState = eMaki;
		toPortrait(3.0f, _maki);
		break;
	}
	case 5: {
		_eState = eDancer1;
		toMask(3.0f, _dancer);
		break;
	}
	case 6: {
		_eState = eDancer2;
		toMask(3.0f, _dancer2);
		break;
	}
	case 7: {
		_eState = eFlower;
		toMask(3.0f, _flower);
		break;
	}
	case 8: {
		movePartical(1.0);
		break;
	}
	case ' ': {
		cross(3.0);
		break;
	}
	}
}

//-----------------------------------
void DPortrait::initPartical()
{
	ofVec2f v(1, 0);
	for (auto& iter : _pList) {
		ofVec2f p = v * ofRandom(0, 100);
		p.rotate(ofRandom(0, 360));
		iter._animPos.setPosition(p);
		iter._animC.setColor(ofColor(ofRandom(100, 200)));
	}
}

//-----------------------------------
void DPortrait::loadPortrait(portraitData& data, string name)
{
	ofImage photo, mask;
	photo.loadImage("portrait/" + name + "_photo.jpg");
	mask.loadImage("portrait/" + name + "_mask.jpg");

	ofPixels maskP = mask.getPixelsRef();
	ofPixels photoP = photo.getPixelsRef();

	vector<ofVec2f> pList;
	for (int x = 0; x < mask.getWidth(); x++)
	{
		for (int y = 0; y < mask.getHeight(); y++)
		{
			int index = (y * mask.getWidth() + x) * 3;
			if ((maskP[index] + maskP[index + 1] + maskP[index + 2]) > cPortraitMaskThreshold)
			{
				pList.push_back(ofVec2f(x, y));
			}
		}
	}

	int interval = (int)ceil(pList.size() / (float)cPortraitUnitSize);

	ZeroMemory(&data.color, sizeof(ofColor) * cPortraitUnitSize);
	if (interval >= 1)
	{
		int index = 0;
		for (int i = 0; i < pList.size(); i += interval, index++)
		{
			auto p = pList[i] * cPortraitMaskToPhoto;
			int photoIdx = (p.y * photo.getWidth() + p.x) * 3;
			data.color[index].r = photoP[photoIdx];
			data.color[index].g = photoP[photoIdx + 1];
			data.color[index].b = photoP[photoIdx + 2];

			data.pos[index] = p - ofVec2f(photo.getWidth() * 0.5, photo.getHeight() * 0.5);
		}
		data.photo = photo;
		data.size = index;
	}
}

//-----------------------------------
void DPortrait::loadMask(maskData & data, string name)
{
	ofImage mask;
	mask.loadImage("portrait/" + name + "_mask.jpg");

	ofPixels maskP = mask.getPixelsRef();

	vector<ofVec2f> pList;
	for (int x = 0; x < mask.getWidth(); x++)
	{
		for (int y = 0; y < mask.getHeight(); y++)
		{
			int index = (y * mask.getWidth() + x) * 3;
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
			auto p = pList[i] * cPortraitMaskToPhoto;
			data.pos[index] = p - ofVec2f(mask.getWidth() * 0.5 * cPortraitMaskToPhoto, mask.getHeight() * 0.5 * cPortraitMaskToPhoto);
		}
		data.size = index;
	}
}

//-----------------------------------
void DPortrait::toColor(float duration, ofColor color)
{
	for (auto& iter : _pList) {
		iter._animC.setDuration(duration * ofRandom(0.8, 0.9));
		iter._animC.animateTo(color);
	}
}

//-----------------------------------
void DPortrait::toCenter(float duration)
{
	ofVec2f v(1, 0);
	for (auto& iter : _pList) {
		iter._animPos.setDuration(duration * ofRandom(0.8, 0.9));
		ofVec2f p = v * ofRandom(0, 20);
		p.rotate(ofRandom(0, 360));
		iter._animPos.animateTo(p);
	}
}

//-----------------------------------
void DPortrait::toCircle(float duration)
{
	ofVec2f v(cPortraitCircleRadius, 0);
	float interval = 360.0f / cPortraitUnitSize;
	for (auto& iter : _pList) {

		iter._animPos.setDuration(duration * ofRandom(0.8, 0.9));
		iter._animPos.animateTo(v);

		ofVec2f p = v * ofRandom(0, 100);
		v.rotate(interval);
	}
}
//-----------------------------------
void DPortrait::toPortrait(float duration, portraitData & data)
{
	for (int i = 0; i < data.size; i++)
	{
		_pList[i]._animC.setDuration(duration * ofRandom(0.8, 0.9));
		_pList[i]._animC.animateTo(data.color[i]);

		_pList[i]._animPos.setDuration(duration * ofRandom(0.8, 0.9));
		_pList[i]._animPos.animateTo(data.pos[i]);
	}

	for (int i = data.size; i < cPortraitUnitSize; i++)
	{
		_pList[i]._animC.setDuration(duration * ofRandom(0.8, 0.9));
		_pList[i]._animC.animateTo(ofColor(0, 0));

		_pList[i]._animPos.setDuration(duration * ofRandom(0.8, 0.9));
		_pList[i]._animPos.animateTo(ofVec2f(0));
	}
}

//-----------------------------------
void DPortrait::toMask(float duration, maskData & data)
{
	for (int i = 0; i < data.size; i++)
	{
		_pList[i]._animC.setDuration(duration * ofRandom(0.8, 0.9));
		_pList[i]._animC.animateTo(ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));

		_pList[i]._animPos.setDuration(duration * ofRandom(0.8, 0.9));
		_pList[i]._animPos.animateTo(data.pos[i]);
	}

	for (int i = data.size; i < cPortraitUnitSize; i++)
	{
		_pList[i]._animC.setDuration(duration * ofRandom(0.8, 0.9));
		_pList[i]._animC.animateTo(ofColor(0, 0));

		_pList[i]._animPos.setDuration(duration * ofRandom(0.8, 0.9));
		_pList[i]._animPos.animateTo(ofVec2f(0));
	}
}

//-----------------------------------
void DPortrait::movePartical(float duration)
{
	for (auto& iter : _pList)
	{
		if (rand() % 10 == 1)
		{
			iter.setMove(ofVec2f(0), duration);

		}
	}
}

//-----------------------------------
void DPortrait::cross(float duration)
{
	_animAlpha.setDuration(duration);
	float alpha = _animAlpha.getCurrentValue();
	if (alpha > 0)
	{
		_animAlpha.animateTo(0.0f);
	}
	else
	{
		_animAlpha.animateTo(255.0f);
	}
}


