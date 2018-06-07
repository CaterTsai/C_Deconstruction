#include "DCyclicCA.h"

//--------------------------------
void DCyclicCA::update(float delta)
{
	CHECK_START();

	_timer -= delta;
	if (_timer <= 0.0f)
	{
		_timer = _generationT;
		nextGeneration();
	}


}

//--------------------------------
void DCyclicCA::draw(int x, int y, int w, int h)
{
	CHECK_START();

	ofPushStyle();
	ofSetColor(255);
	ofFill();
	{
		auto halfW = w * 0.5f;
		auto halfH = h * 0.5f;
		auto unitW = w / (float)cWorldWidth;
		auto unitH = h / (float)cWorldHeight;
		for (int tx = 0; tx < cWorldWidth; tx++)
		{
			for (int ty = 0; ty < cWorldHeight; ty++)
			{
				auto index = tx + ty * cWorldWidth;
				ofSetColor(_colorSet[_nowGeneration[index]]);
				ofDrawRectangle((tx * unitW) + x, (ty * unitH) + y, unitW, unitH);
			}
		}
	}
	ofPopStyle();
}

//--------------------------------
void DCyclicCA::start()
{
	_isStart = true;
	_neighborIndex = getNeighborIndex(_range, _type);
	initPattern();
	createWorld();

	_timer = _generationT;
}

//--------------------------------
void DCyclicCA::stop()
{
	_isStart = false;
}

//--------------------------------
void DCyclicCA::set(int r, int t, int s, eNeighbouring type)
{
	_range = r;
	_threshold = t;
	_stateNum = s;
	_type = type;

	_neighborIndex = getNeighborIndex(_range, _type);
}

//--------------------------------
void DCyclicCA::createWorld()
{
	_nowGeneration = _worldA.begin();
	_nextGeneration = _worldB.begin();

	for (int tx = 0; tx < cWorldWidth; tx++)
	{
		for (int ty = 0; ty < cWorldHeight; ty++)
		{
			auto index = tx + ty * cWorldWidth;
			_nowGeneration[index] = rand() % _stateNum;
			_nextGeneration[index] = 0;
		}
	}
}

//--------------------------------
void DCyclicCA::initPattern()
{
	_colorSet.clear();
	ofColor color(34, 80, 89);
	float b = color.getBrightness();
	float IntB = (255.0f - b) / _stateNum;
	for (int i = 0; i < _stateNum; i++)
	{
		_colorSet.push_back(color);
		color.setBrightness(b + IntB * i);
		
	}
}

//--------------------------------
void DCyclicCA::nextGeneration()
{
	for (int x = 0; x < cWorldWidth; x++)
	{
		for (int y = 0; y < cWorldHeight; y++)
		{
			evolution(x, y);
		}
	}
	swap(_nowGeneration, _nextGeneration);
}

//--------------------------------
void DCyclicCA::evolution(int x, int y)
{
	int count = 0;
	unsigned char state = _nowGeneration[x + y * cWorldWidth];
	for (auto& iter : _neighborIndex)
	{
		int nx, ny;
		nx = x + iter.x;
		ny = y + iter.y;
		if (nx < 0) nx += cWorldWidth;
		if (nx >= cWorldWidth) nx -= cWorldWidth;
		if (ny < 0) ny += cWorldWidth;
		if (ny >= cWorldHeight) ny -= cWorldHeight;

		if (_nowGeneration[nx + ny * cWorldWidth] == (state + 1) % _stateNum)
		{
			count++;
		}
	}

	if (count >= _threshold)
	{
		_nextGeneration[x + y * cWorldWidth] = (state + 1) % _stateNum;
	}
	else
	{
		_nextGeneration[x + y * cWorldWidth] = state;
	}
}

//--------------------------------
vector<ofVec2f> DCyclicCA::getNeighborIndex(int r, eNeighbouring type)
{
	vector<ofVec2f> returnV;
	if (type == eNeighbouring::eMoore)
	{
		for (int i = 1; i <= r; i++)
		{
			for (int y = -i; y <= i; y++)
			{
				for (int x = -i; x <= i; x++)
				{
					if (x == 0 && y == 0)
					{
						continue;
					}
					returnV.push_back(ofVec2f(x, y));
				}
			}
		}
	}
	else
	{
		for (int i = 1; i <= r; i++)
		{
			for (int y = -i; y <= i; y++)
			{
				for (int x = -i; x <= i; x++)
				{
					if (x == 0 && y == 0)
					{
						continue;
					}

					if (abs(y) + abs(x) <= r)
					{
						returnV.push_back(ofVec2f(x, y));
					}
				}
			}
		}
	}
	return returnV;
}
