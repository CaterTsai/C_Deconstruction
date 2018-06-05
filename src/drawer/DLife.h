#pragma once

#include "DBase.h"

class DLife : public DBase
{
#pragma region Life Element
	enum eLifeType
	{
		eNormal = 0
		,eStrong
		,eFast
		,eLifeNum
	};

	class LifeElement
	{
	public:
		LifeElement()
			:_live(false)
		{
			setType(eNormal);
		}

		inline bool getLive()
		{
			return _live;
		}
		inline void setLive(bool live)
		{
			_live = live;
		}

		inline eLifeType getType()
		{
			return _type;
		}

		inline int getGeneration()
		{
			return _generation;
		}

		void setType(eLifeType type);
		void evolution(int counter, eLifeType type);
		

	private:
		bool _live;
		eLifeType _type;
		int _liveMax, _liveMin;
		int _dieMax, _dieMin;
		int _generation;
	};
#pragma endregion


public:
	DLife()
		:DBase(eDLife)
		,_generationT(0.02f)
	{
		_canvas.allocate(1024, 1024, GL_RGB);
		

	}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;
	void draw() override;
	void start() override;
	void stop() override;

	void setSphere(ofVec2f pos, float size);

private:
	void createWorld();
	void setPattern(int x, int y);
	void nextGeneration();
	void evolution(int x, int y);

	void drawOnCanvas();
	
private:
	ofFbo _canvas;
	float _generationT;
	ofSpherePrimitive _sphere;
	LifeElement* _nowGeneration;
	LifeElement* _nextGeneration;
	LifeElement _worldA[cWorldHeight * cWorldWidth];
	LifeElement _worldB[cWorldHeight * cWorldWidth];
};