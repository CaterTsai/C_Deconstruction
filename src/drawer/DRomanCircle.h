#pragma once

#include "DBase.h"

class DRomanCircle : public DBase
{
#pragma region circleUnit
private:
	class circleUnit
	{
	public:
		circleUnit();

	private:
		ofMesh _mesh;
		ofImage _tex;

		
	};
#pragma endregion

private:

public:
	DRomanCircle()
		:DBase(eDRomanCircle)
	{
		ofDisableArbTex();
		_img.loadImage("pattern_5.png");

		_tex = _img.getTextureReference();
		_tex.setTextureWrap(GL_REPEAT, GL_REPEAT);
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void trigger() override;
private:
	void generate();

private:
	ofMesh _mesh;
	ofImage _img;
	ofTexture _tex;
};