#pragma once

#include "DBase.h"

class DCyclicCA : public DBase
{
private:
	typedef array<unsigned char, cWorldHeight * cWorldWidth> worldType;
	typedef worldType::iterator worldTypeIter;
public:
	enum eNeighbouring
	{
		eMoore = 0
		, eVonNeumann
	};

public:
	DCyclicCA()
		:DBase(eDCyclicCA)
		, _generationT(0.05f)
		, _range(1)
		, _threshold(3)
		, _stateNum(3)
		, _type(eNeighbouring::eMoore)
	{
	}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;
	void start() override;
	void stop() override;

	void set(int r, int t, int s, eNeighbouring type);

private:
	void createWorld();
	
	void nextGeneration();
	void evolution(int x, int y);

	vector<ofVec2f> getNeighborIndex(int r, eNeighbouring type);
	void initPattern();
private:
	float _timer;
	vector<ofColor> _colorSet;
	vector<ofVec2f> _neighborIndex;

	eNeighbouring _type;
	int _range, _threshold, _stateNum;

	float _generationT;
	worldTypeIter _nowGeneration, _nextGeneration;
	worldType _worldA, _worldB;
};