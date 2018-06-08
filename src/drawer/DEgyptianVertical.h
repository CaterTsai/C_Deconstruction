#pragma once

#include "DBase.h"
#include "ofxAnimatableFloat.h"
#include "ofxTrueTypeFontUC.h"

class DEgyptianVertical : public DBase
{
private:
	class verticalUnit
	{
	public:
		verticalUnit():
			_isMove(true),
			_startChange(false)
		{};
		verticalUnit(int x);

		void update(float delta);
		void draw(ofxTrueTypeFontUC& font);

		void in();
		void out();
		void toggle();

		void startChange();
		void stopChange();

		void startMove();
		void stopMove();

	private:
		void generatorText();
		void changeText();
	private:
		bool _startChange, _isMove;
		ofVec2f _pos;
		float _yv;
		array<bool, cEgyptianVerticalTextNum> _changeIdx;
		array<string, cEgyptianVerticalTextNum> _text;
		ofxAnimatableFloat _animAlpha;
		
	};

public:
	DEgyptianVertical()
		:DBase(eDEgyptianVertical)
	{
		loadFont();
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void trigger(int key) override;

private:
	void loadFont();
	void initVertiaclUnit();

private:
	vector<verticalUnit> _vUnitMgr;
	ofxTrueTypeFontUC _font;
};