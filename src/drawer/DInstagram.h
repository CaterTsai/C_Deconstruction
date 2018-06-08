#pragma once

#include "DBase.h"
#include "ofxAnimatableFloat.h"

class DInstagram : public DBase
{
public:
	DInstagram()
		:DBase(eDInstagram)
	{
		loadImage();
	}

	void update(float delta) override;
	void draw(int x, int y, int z = 0) override;

	void start() override;
	void stop() override;

	void trigger(int key) override;

private:
	void loadImage();
	void next(int user);
private:
	
	int _nowUserId, _nowPhotoId;
	int _nextUserId, _nextPhotoId;
	ofImage _cover;
	array<ofImage, 2> _users;
	array<vector<ofImage>, 2> _photoList;
	ofxAnimatableFloat _animSlide;
};