#pragma once

#include "DBase.h"
#include "ofxAnimatableFloat.h"

class DBreeze : public DBase
{

#pragma region partical
public:
	enum ePType {

	};
private:
	class partical {
	public:
		partical()
			:_pos(0.0f)
			,_vec(0.0f)
		{}

		void set(ofVec2f p, ofVec2f v, ofVec2f a, float t);
		void update(float delta, ofVec2f desired);

	public:
		ofVec2f _pos, _vec;
		float _life;
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

	void emitter();

private:
	list<partical> _pList;
	ofVec2f _flowFields[cFieldRows][cFieldCols];
};