#pragma once

#include "DBase.h"
#include "ofxAnimatableOfColor.h"
#include "ofxAnimatableOfPoint.h"




class DPortrait : public DBase
{
private:
	struct portraitData
	{
		ofImage photo;
		array<ofVec2f, cPortraitUnitSize> pos;
		array<ofColor, cPortraitUnitSize> color;
		int size;
	};

	//------------------------
	//CLASS pUnit
	class pUnit {
	public:
	private:
		ofxAnimatableOfColor _animC;
		ofxAnimatableOfPoint _animPos;
	};

public:
	DPortrait()
		:DBase(eDPortrait)
	{
		loadPortrait();
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void trigger(int key) override;

private:
	void loadPortrait();

private:
	portraitData _weber;
};