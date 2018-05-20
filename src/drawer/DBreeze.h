#pragma once

#include "DBase.h"
#include "ofxAnimatableFloat.h"

class DBreeze : public DBase
{

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



private:
	ofVec2f _flowFields[cFieldRows][cFieldCols];
};