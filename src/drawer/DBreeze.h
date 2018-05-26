#pragma once

#include "DBase.h"
#include "ofxAnimatableFloat.h"

class DBreeze : public DBase
{

#pragma region partical
public:
	enum ePType :int{
		ePCircle = 0 //2D
		,ePRect
		,ePTriangle
		,ePBox //3D
		,ePSphere
		,ePCone
		,ePCylinder
		,ePTypeNum
		,ePTypeRandom
	};
private:
	class partical {
	public:
		partical()
			:_pos(0.0f)
			, _vec(0.0f)
			, _type(ePTypeNum)
			, _degree(0.0f)
			, _rotateV(ofRandom(-180, 180))
			,_size(ofRandom(cBreezParticalSizeMin, cBreezParticalSizeMax))
		{
			_axis.set(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
			_axis.normalize();
		}

		void set(ePType type, ofVec2f p, ofVec2f v, ofVec2f a, float t);
		void update(float delta, ofVec2f desired);

	public:
		ePType _type;
		ofVec2f _pos, _vec;
		float _life, _lifeLength;

		float _size;
		ofVec3f _axis;
		float _degree, _rotateV;
	};
#pragma endregion


public:
	DBreeze()
		:DBase(eDBreeze)
	{
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void trigger(int key) override;

private:
	void generateFlowFields();
	void displayFlow(int x, int y, int w, int h);
	ofVec2f getFlow(ofVec2f pos);

	void checkPartical();
	void drawPartical(partical& p);
	void emitter(ePType type = ePTypeRandom);

private:

	list<partical> _pList;
	ofVec2f _flowFields[cFieldRows][cFieldCols];
};