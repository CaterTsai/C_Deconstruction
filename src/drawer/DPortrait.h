#pragma once

#include "DBase.h"
#include "ofxAnimatableOfColor.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableFloat.h"



class DPortrait : public DBase
{
private:
	//------------------------
	//CLASS pUnit
	class pUnit {
	public:
		pUnit():
			_offset(0),
			_offsetV(0)
		{}
		void update(float detla);
		void setMove(ofVec2f pos, float duration);
	public:
		ofVec2f _offset, _offsetV;
		ofxAnimatableOfColor _animC;
		ofxAnimatableOfPoint _animPos;
	};

	struct portraitData
	{
		ofImage photo;
		array<ofVec2f, cPortraitUnitSize> pos;
		array<ofColor, cPortraitUnitSize> color;
		int size;
	};

	struct maskData
	{
		array<ofVec2f, cPortraitUnitSize> pos;
		int size;
	};


public:
	DPortrait()
		:DBase(eDPortrait)
		, _rotate(0)
	{
		loadPortrait(_weber, "weber");
		loadPortrait(_tiny, "tiny");
		loadPortrait(_maki, "maki");
		loadMask(_dancer, "dancer");
		loadMask(_dancer2, "dancer2");
		loadMask(_flower, "flower");
	}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;
	void drawPhoto(int w, int h);
	void start() override;
	void stop() override;

	void trigger(int key) override;
	void togglePhoto();
	void setRotateV(float rv);
	void setColorR(float r);
private:
	void initPartical();
	void loadPortrait(portraitData& data, string name);
	void loadMask(maskData& data, string name);

	void toColor(float duration, ofColor color);

	void toCenter(float duration);
	void toCircle(float duration);
	void toPortrait(float duration, portraitData& data);
	void toMask(float duration, maskData& data);

	void movePartical(float duration);

	void cross(float duration);
	

private:
	enum eState {
		eCenter = 0
		,eCircle
		,eWeber
		,eTiny
		,eMaki
		,eDancer1
		,eDancer2
		,eFlower
	}_eState;

	bool _showPhoto;
	portraitData _weber, _tiny, _maki;
	maskData _dancer, _dancer2, _flower;
	array<pUnit, cPortraitUnitSize> _pList;
	ofxAnimatableFloat _animAlpha;

	float _rotate, _rotateV;
	ofColor _color;
};