#include "DInstagram.h"

//-----------------------------------
void DInstagram::update(float delta)
{
	CHECK_START();

	_animSlide.update(delta);

	if (_animSlide.hasFinishedAnimating() && _animSlide.getPercentDone() == 1.0f)
	{
		_nowUserId = _nextUserId;
		_nowPhotoId = _nextPhotoId;
	}
}

//-----------------------------------
void DInstagram::draw(int x, int y, int z)
{
	CHECK_START();
	ofPushMatrix();
	ofTranslate(x, y);
	ofPushStyle();
	ofSetColor(255);


	ofPushMatrix();
	ofTranslate(0, 105);
	if (_animSlide.isAnimating())
	{
		float slideVal = _animSlide.getCurrentValue();
		float moveDist = slideVal * _users[_nowUserId].getHeight();

		_users[_nowUserId].draw(0, -moveDist);
		_photoList[_nowUserId][_nowPhotoId].draw(0, -moveDist + 82);

		_users[_nextUserId].draw(0, _users[_nowUserId].getHeight() - moveDist);
		_photoList[_nextUserId][_nextPhotoId].draw(0, _users[_nowUserId].getHeight() - moveDist + 82);
	}
	else
	{
		_users[_nowUserId].draw(0, -0);
		_photoList[_nowUserId][_nowPhotoId].draw(0, 82);
	}

	ofPopMatrix();

	_cover.draw(0, 0);
	ofPopStyle();
	ofPopMatrix();
}

//-----------------------------------
void DInstagram::start()
{
	_isStart = true;

	_nowUserId = _nowPhotoId = 0;

	_animSlide.reset(0);
}

//-----------------------------------
void DInstagram::stop()
{
	_isStart = false;
}

//-----------------------------------
void DInstagram::trigger(int key)
{
	switch (key)
	{
	case 0:
	case 1:
	{
		next(key);
		break;
	}
	}
}

//-----------------------------------
void DInstagram::loadImage()
{
	_cover.load("instagram/ui_front.png");
	_users[0].load("instagram/1-temp.jpg");
	_users[1].load("instagram/2-temp.jpg");


	for (int i = 0; i < 5; i++)
	{
		ofImage img1, img2;
		img1.load("instagram/1_" + ofToString(i + 1) + ".jpg");
		img2.load("instagram/2_" + ofToString(i + 1) + ".jpg");
		_photoList[0].push_back(img1);
		_photoList[1].push_back(img2);
	}
}

//-----------------------------------
void DInstagram::next(int user)
{
	_nextUserId = user;
	_nextPhotoId = (_nowPhotoId + 1) % _photoList[_nextUserId].size();

	_animSlide.setDuration(1.0);
	_animSlide.animateFromTo(0.0f, 1.0f);
}
