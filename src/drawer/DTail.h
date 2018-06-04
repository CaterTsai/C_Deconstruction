#pragma once

#include "DBase.h"

class DTail : public DBase
{
#pragma region Tail
	struct tailUnit {
		ofVec2f pos;
		ofVec2f decline[2];
		float lifeT;
	};

	class tail {
	public:
		tail();
		~tail();
		void set(float lifeT, float width, bool isDecline, float declineT);
		void update(float delta);
		void draw();
		void addPos(ofVec2f p);

	private:
		bool _isDecline;
		list<tailUnit> _tailUnitList;
		ofMesh _tailMesh;
		float _tailLifeT;
		float _width, _declineT;
	};
#pragma endregion


#pragma region partical
private:
	class partical {
	public:
		partical()
			:_pos(0.0f)
			, _vec(0.0f)
			, _growTail(true)
			, _size(ofRandom(cBreezParticalSizeMin, cBreezParticalSizeMax))
		{
		}

		void set(ofVec2f p, ofVec2f v, ofVec2f a, float t);
		void update(float delta, ofVec2f desired);

	public:
		ofVec2f _pos, _vec;
		float _life, _lifeLength;
		float _size;
		bool _growTail;
		tail _tail;
	};
#pragma endregion


public:
	DTail()
		:DBase(eDTail)
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
	void emitter();

private:
	list<partical> _pList;
	ofVec2f _flowFields[cFieldRows][cFieldCols];
};