#include "DBreeze.h"

#pragma region partical
//--------------------------------------
void DBreeze::partical::set(ePType type, ofVec2f p, ofVec2f v, ofVec2f a, float t)
{
	_type = type;
	_pos.set(p);
	_vec.set(v);
	_lifeLength = _life = t;
}

//--------------------------------------
void DBreeze::partical::update(float delta, ofVec2f desired)
{
	if (_life <= 0.0f)
	{
		//Dead
		return;
	}

	ofVec2f steer = desired - _vec;
	_vec += steer * delta;
	_pos += _vec * delta;

	if (_pos.x > cBreezRange.getMaxX())
	{
		_pos.x -= cBreezRange.getMaxX();
	}
	else if (_pos.x < cBreezRange.getMinX())
	{
		_pos.x += cBreezRange.getWidth();
	}

	if (_pos.y > cBreezRange.getMaxY())
	{
		_pos.y -= cBreezRange.getMaxY();
	}
	else if (_pos.y < cBreezRange.getMinY())
	{
		_pos.y += cBreezRange.getHeight();
	}
	_life -= delta;
}
#pragma endregion


//--------------------------------------
void DBreeze::update(float delta)
{
	CHECK_START();

	for (auto& iter : _pList)
	{
		iter.update(delta, getFlow(iter._pos));
	}

	checkPartical();
}

//--------------------------------------
void DBreeze::draw()
{
	CHECK_START();

	//Debug
	//displayFlow(0, 0, cWindowWidth, cWindowHeight);

	ofPushStyle();
	ofNoFill();
	
	for (auto& iter : _pList)
	{
		ofSetColor(255, iter._life / iter._lifeLength * 255.0f);
		ofDrawCircle(iter._pos, 5);
	}
	ofPopStyle();
}

//--------------------------------------
void DBreeze::start()
{
	generateFlowFields();
	_isStart = true;
}

//--------------------------------------
void DBreeze::stop()
{
	_isStart = false;
}

//--------------------------------------
void DBreeze::trigger(int key)
{
	if (key == ' ')
	{
		emitter();
	}
	
}

//--------------------------------------
void DBreeze::generateFlowFields()
{
	float offset = 0.05;
	for (int i = 0; i < cFieldRows; i++)
	{
		for (int j = 0; j < cFieldCols; j++)
		{
			//float theta = ofMap(ofNoise(i * offset, j * offset), 0, 1, 0, TWO_PI);
			float theta = ofRandom(-PI / 2.0f, PI / 2.0f);
			ofVec2f desired(cos(theta), sin(theta));
			_flowFields[i][j].set(desired.normalized() * 500);
		}
	}
}

//--------------------------------------
void DBreeze::displayFlow(int x, int y, int w, int h)
{
	ofPushStyle();
	ofSetColor(255);
	ofFill();
	float unitW, unitH;
	unitW = w / cFieldCols;
	unitH = h / cFieldRows;

	for (int i = 0; i < cFieldRows; i++)
	{
		for (int j = 0; j < cFieldCols; j++)
		{
			ofVec2f center(j * unitW + unitW * 0.5, i * unitH + unitH * 0.5);
			ofVec2f desired = _flowFields[i][j];
			desired.normalize();
			ofVec2f end = center + (desired * 0.5 * unitW);

			ofDrawCircle(center, 0.2 * unitW);
			ofLine(center, end);
		}
	}
	ofPopStyle();
}

//--------------------------------------
ofVec2f DBreeze::getFlow(ofVec2f pos)
{
	int x = static_cast<int>(((pos.x - cBreezRange.x) / cBreezRange.width) * cFieldCols);
	int y = static_cast<int>(((pos.y - cBreezRange.y) / cBreezRange.height) * cFieldRows);

	x = (x == cFieldCols) ? x - 1 : x;
	y = (y == cFieldRows) ? y - 1 : y;
	return _flowFields[y][x];
}

//--------------------------------------
void DBreeze::checkPartical()
{
	_pList.remove_if([](const partical & p)
	{
		return p._life < 0.0f;
	});
}

//--------------------------------------
void DBreeze::emitter()
{
	partical newP;
	float theta = ofRandom(-PI / 4.0f, PI / 4.0f);
	ofVec2f pos(cBreezRange.getMinX(), ofRandom(cBreezRange.getMinY(), cBreezRange.getMaxY()));
	ofVec2f vec(cos(theta), sin(theta));
	ofVec2f acc(0);
	float lifeT = ofRandom(10, 20);
	vec *= ofRandom(cBreezParticalSpeedMin, cBreezParticalSpeedMax);
	newP.set(pos, vec, acc, lifeT);

	_pList.push_back(newP);
}


