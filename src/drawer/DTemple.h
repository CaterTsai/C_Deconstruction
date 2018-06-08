#pragma once

#include "DBase.h"
#include "ofxAssimpModelLoader.h"
#include "ofxAnimatableOfColor.h"
#include "ofxAnimatableOfPoint.h"

class DTemple : public DBase
{
private:
	class lightUnit {
	public:
		lightUnit():
			_isOn(false)
			, _isChangeHue(false)
		{};
		void update(float delta);

		void lightTo(float t, ofColor target);

		void lightOff(float t);
		void toggle(float t, ofColor target);

		void startMove(float t, ofVec3f start, ofVec3f end);
		void stopMove();

	public:
		bool _isOn, _isChangeHue;
		ofLight _light;
		ofxAnimatableOfColor _animColor;
		ofxAnimatableOfPoint _animMove;

	};

public:
	DTemple()
		:DBase(eDTemple)
	{
		loadPillar();
		
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void trigger(int key) override;

	void setColorG(int g);
private:
	void loadPillar();
	void initLight();
private:
	ofColor _color;
	
	array<lightUnit, cTemplePillarRowNum> _lightMgr;
	vector<ofVec3f> _pillarMgr;
	ofxAssimpModelLoader _pillar;
};