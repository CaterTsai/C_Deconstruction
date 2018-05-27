#pragma once

#include "DBase.h"
#include "ofxAssimpModelLoader.h"

class DTemple : public DBase
{
private:
	class pillarUnit {
	public:
		pillarUnit(ofVec3f pos, bool isLeft)
			:_pos(pos)
			,_alpha(255.0)
		{
		}

		void update(float delta);
	public:
		float _alpha;
		ofVec3f _pos;

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

private:
	void loadPillar();
	void initLight();
private:
	ofPoint _lightV;
	ofLight _light;
	vector<pillarUnit> _pillarMgr;
	ofxAssimpModelLoader _pillar;
};