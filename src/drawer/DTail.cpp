#include "DTail.h"

#pragma region Tail
//--------------------------------------
DTail::tail::tail()
	:_width(3.0f)
	,_declineT(2.0f)
{
	_tailMesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLES);

}

//--------------------------------------
void DTail::tail::set(float width, float declineT)
{
	_width = width;
	_declineT = declineT;
}

//--------------------------------------
void DTail::tail::update(float delta)
{
	if (_tailUnitList.size() < 2)
	{
		return;
	}
	int index = 0;
	for (auto& iter : _tailUnitList)
	{
		if (index == 0)
		{
			continue;
		}


		auto p1 = _tailMesh.getVertex(index * 2);
		auto p2 = _tailMesh.getVertex(index * 2 + 1);

		p1 += delta * iter.decline[0];
		p2 += delta * iter.decline[1];

		_tailMesh.setVertex(index, p1);
		_tailMesh.setVertex(index, p2);

		index++;
	}
}

//--------------------------------------
void DTail::tail::draw()
{
	ofPushStyle();
	ofSetColor(255);
	_tailMesh.drawWireframe();
	ofPopStyle();
}

//--------------------------------------
void DTail::tail::addPos(ofVec2f p)
{
	tailUnit newTailUnit;
	newTailUnit.pos = p;

}

#pragma endregion


#pragma region partical
//--------------------------------------
void DTail::partical::set(ofVec2f p, ofVec2f v, ofVec2f a, float t)
{
	_pos.set(p);
	_vec.set(v);
	_lifeLength = _life = t;
}

//--------------------------------------
void DTail::partical::update(float delta, ofVec2f desired)
{
	if (_life <= 0.0f)
	{
		//Dead
		return;
	}

	ofVec2f steer = desired - _vec;
	_vec += steer * delta;
	_pos += _vec * delta;


	//Move
	if (_pos.x > cBreezRange.getMaxX())
	{
		_life = 0;
	}
	else if (_pos.x < cBreezRange.getMinX())
	{
		_life = 0;
	}

	if (_pos.y > cBreezRange.getMaxY())
	{
		_life = 0;
	}
	else if (_pos.y < cBreezRange.getMinY())
	{
		_life = 0;
	}
	_life -= delta;
}
#pragma endregion

//--------------------------------------
void DTail::update(float delta)
{
	CHECK_START();

	for (auto& iter : _pList)
	{
		iter.update(delta, getFlow(iter._pos));
	}

	checkPartical();
}

//--------------------------------------
void DTail::draw()
{
	CHECK_START();

	//Debug
	//displayFlow(0, 0, cWindowWidth, cWindowHeight);

	ofPushStyle();
	ofNoFill();

	for (auto& iter : _pList)
	{
		ofSetColor(255, iter._life / iter._lifeLength * 255.0f);
		drawPartical(iter);
	}
	ofPopStyle();
}

//--------------------------------------
void DTail::start()
{
	generateFlowFields();
	_isStart = true;
}

//--------------------------------------
void DTail::stop()
{
	_isStart = false;
}

//--------------------------------------
void DTail::trigger(int key)
{
	if (key == ' ')
	{
		emitter();
	}

}

//--------------------------------------
void DTail::generateFlowFields()
{
	float offset = 0.05;
	for (int i = 0; i < cFieldRows; i++)
	{
		for (int j = 0; j < cFieldCols; j++)
		{
			//float theta = ofMap(ofNoise(i * offset, j * offset), 0, 1, 0, TWO_PI);
			float theta = ofRandom(-PI * 0.75, -PI * 0.25f);
			ofVec2f desired(cos(theta), sin(theta));
			_flowFields[i][j].set(desired.normalized() * 500);
		}
	}
}

//--------------------------------------
void DTail::displayFlow(int x, int y, int w, int h)
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
ofVec2f DTail::getFlow(ofVec2f pos)
{
	int x = static_cast<int>(((pos.x - cBreezRange.x) / cBreezRange.width) * cFieldCols);
	int y = static_cast<int>(((pos.y - cBreezRange.y) / cBreezRange.height) * cFieldRows);

	x = (x == cFieldCols) ? x - 1 : x;
	y = (y == cFieldRows) ? y - 1 : y;
	return _flowFields[y][x];
}

//--------------------------------------
void DTail::checkPartical()
{
	_pList.remove_if([](const partical & p)
	{
		return p._life < 0.0f;
	});
}

//--------------------------------------
void DTail::drawPartical(partical& p)
{

}

//--------------------------------------
void DTail::emitter()
{
	partical newP;
	float theta = ofRandom(-PI / 4.0f, PI / 4.0f);
	ofVec2f pos(cBreezRange.getMinX(), ofRandom(cBreezRange.getMinY(), cBreezRange.getMaxY()));
	ofVec2f vec(cos(theta), sin(theta));
	ofVec2f acc(0);


	float lifeT = ofRandom(5, 15);
	vec *= ofRandom(cBreezParticalSpeedMin, cBreezParticalSpeedMax);
	newP.set(pos, vec, acc, lifeT);

	_pList.push_back(newP);
}
