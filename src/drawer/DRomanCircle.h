#pragma once

#include "DBase.h"
#include "ofxAnimatableFloat.h"

class DRomanCircle : public DBase
{
#pragma region circleUnit
private:
	class circleUnit
	{
	public:
		circleUnit(string texPath, float r, float depth, float size);
		void update(float delta);
		void draw();
		void in(float t);
		void out(float t);
		void trigger(float t);

	private:
		ofMesh _mesh;
		ofImage _tex;
		ofxAnimatableFloat _animAlpha;
		float _rotateD;
		float _rotateV;

	};
#pragma endregion

private:

public:
	DRomanCircle()
		:DBase(eDRomanCircle)
	{
		ofDisableArbTex();	
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void trigger(int key) override;
private:
	void initMesh();

private:
	vector<circleUnit> _circleList;
};