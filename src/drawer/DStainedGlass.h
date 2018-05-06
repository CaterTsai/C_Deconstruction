#pragma once

#include "DBase.h"
#include "shaderVoronoi.h"

class DStainedGlass : public DBase
{

public:
	DStainedGlass()
		:DBase(eDStainedGlass)
	{
		_img.load("test.jpg");
		
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void trigger(int key) override;

private:
	void initVoronoi();
private:
	ofImage _img;
	shaderVoronoi _voronoi;
};