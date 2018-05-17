#pragma once

#include "DBase.h"
#include "shaderVoronoi.h"
#include "ofxLayerMask.h"

class DStainedGlass : public DBase
{

#pragma region mask
private:
	enum eMaskType : int
	{
		eMaskWindow = 0 // Can't rotate
		, eMaskCircle
	};

private:
	class mask
	{
	public:
		mask(string path, eMaskType type);
		void draw(int cx, int cy, int width, int height);

		void setRotate(float rotateV);
		int getType();

	private:
		ofImage _mask;
		float _r, _rV;
		eMaskType _type;
	};
#pragma endregion

public:
	DStainedGlass()
		:DBase(eDStainedGlass)
		, _rotate(0.0f)
		, _rotateV(0.0f)
	{
		_img.load("glassPattern.jpg");
		initMask();
		_masker.setup(cVoronoiWidth, cVoronoiHeight);
		_masker.newLayer();
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void trigger(int key) override;
	void startRotate(float rv);

private:
	void initMask();
	void initVoronoi();

	void setSeed();
	void updateSeed(float delta);
private:
	ofImage _img;

	int _maskIdx;
	float _rotate, _rotateV;

	vector<mask> _maskMgr;
	vector<ofVec2f> _seedV;
	shaderVoronoi _voronoi;
	ofxLayerMask _masker;
};