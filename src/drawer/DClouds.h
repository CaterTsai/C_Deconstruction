#pragma once

#include "DBase.h"
#include "ofxAnimatableFloat.h"

class DClouds : public DBase
{
private:
	enum eCloudType {
		eCloudImg = 0
		,eCloudPartical
	};

	class cloudUnit {
	public:
		cloudUnit():
			_anim(0.0f)
			, _animV(0.0f)
			, _cloudIdx(0)
		{}

		void update(float delta);
		void set(int cloudIndex);
		void set(ofColor color);

	private:
		void init();
	public:

		eCloudType _eType;

		int _cloudIdx;

		ofColor _c;
		ofxAnimatableFloat _animAlpha;
		
		ofVec2f _source, _target;
		float _anim, _animV;
	};
public:
	DClouds()
		:DBase(eDCloud)
	{
		loadClouds();
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void trigger(int key) override;

private:
	void loadClouds();

	void addPartical();
	void addCloudUnit();

private:
	list<cloudUnit> _cloudPartical;
	list<cloudUnit> _cloudList;
	array<ofImage, cCloudImgNum> _cloudsImg;
};