#include "DRomanCircle.h"


#pragma region circleUnit
//------------------------------------
DRomanCircle::circleUnit::circleUnit(string texPath, float r, float depth, float size)
	:_rotateD(ofRandom(0.0f, 360.0f))
{
	if (!_tex.load(texPath))
	{
		ofLog(OF_LOG_ERROR, "[circleUnit]Load Texture failed :" + texPath);
	}
	else
	{
		//Generator Mesh
		auto asp = _tex.getWidth() / _tex.getHeight();
		auto length = depth * asp;
		float delta = (length / (r * TWO_PI)) * 360.0f;
		_mesh.clear();
		
		ofVec2f v(0, -1);

		for (int i = 0; i < size; i++)
		{
			ofVec2f p1, p2;
			p1 = v * r;
			p2 = p1 + v * depth;

			_mesh.addVertex(p1);
			_mesh.addTexCoord(ofVec2f(i, 0));

			_mesh.addVertex(p2);
			_mesh.addTexCoord(ofVec2f(i, 1.0));
			v.rotate(delta);
		}
		_mesh.enableTextures();
		_mesh.enableIndices();
		_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLE_STRIP);

		//Others
		_tex.getTextureReference().setTextureWrap(GL_REPEAT, GL_REPEAT);
		_animAlpha.reset(0);
		_rotateV = (rand() % 2 == 0?-1:1) * ofRandom(2, 15);

	}
}

//------------------------------------
void DRomanCircle::circleUnit::update(float delta)
{
	_animAlpha.update(delta);
	
	_rotateD += _rotateV * delta;
	if (_rotateD > 360.0f)
	{
		_rotateD -= 360.0f;
	}
	else if (_rotateD < 0.0f)
	{
		_rotateD += 360.0f;
	}
}

//------------------------------------
void DRomanCircle::circleUnit::draw()
{
	ofPushStyle();
	ofSetColor(255, _animAlpha.getCurrentValue());
	{
		ofPushMatrix();
		ofTranslate(0, 0);
		ofRotateZ(_rotateD);
		_tex.getTextureReference().setTextureWrap(GL_REPEAT, GL_REPEAT);
		_tex.getTextureReference().bind();
		_mesh.draw();
		_tex.getTextureReference().unbind();
		ofPopMatrix();
	}
	ofPopStyle();
}

//------------------------------------
void DRomanCircle::circleUnit::in(float t)
{
	_animAlpha.setDuration(t);
	_animAlpha.animateFromTo(0.0f, 255.0f);
}

//------------------------------------
void DRomanCircle::circleUnit::out(float t)
{
	_animAlpha.setDuration(t);
	_animAlpha.animateFromTo(255.0f, 0.0f);
}

//------------------------------------
void DRomanCircle::circleUnit::trigger(float t)
{
	if (_animAlpha.isAnimating())
	{
		if (_animAlpha.getCurrentSpeed() > 0)
		{
			_animAlpha.setDuration(t);
			_animAlpha.animateTo(0.0f);
		}
		else
		{
			_animAlpha.setDuration(t);
			_animAlpha.animateTo(255.0f);
		}
	}
	else
	{
		if (_animAlpha.getCurrentValue() == 0)
		{
			in(t);
		}
		else if (_animAlpha.getCurrentValue() == 255)
		{
			out(t);
		}
	}
}
#pragma endregion

//------------------------------------
void DRomanCircle::update(float delta)
{
	CHECK_START();
	for (auto& iter : _circleList)
	{
		iter.update(delta);
	}
}

//------------------------------------
void DRomanCircle::draw()
{
	CHECK_START();

	for (auto& iter : _circleList)
	{
		iter.draw();
	}

}

//------------------------------------
void DRomanCircle::start()
{
	//initMesh();
	_isStart = true;

}

//------------------------------------
void DRomanCircle::stop()
{
	_isStart = false;
}

//------------------------------------
void DRomanCircle::trigger(int key)
{
	if (key >= 0 && key < _circleList.size())
	{
		_circleList[key].trigger(1.0);
	}
	
}

//------------------------------------
void DRomanCircle::initMesh()
{
	_circleList.clear();
	float r = 200;

	circleUnit newCircle1(("pattern/pattern_6.png"), r, 40, rand() % 25 + 15);
	r += 40;

	circleUnit newCircle2(("pattern/pattern_2.png"), r, 30, rand() % 30 + 15);
	r += 30;

	circleUnit newCircle3(("pattern/pattern_1.png"), r, 40, rand() % 30 + 20);
	r += 40;

	circleUnit newCircle4(("pattern/pattern_7.png"), r, 25, rand() % 20 + 20);
	r += 25;

	circleUnit newCircle5(("pattern//pattern_5.png"), r, 40, rand() % 30 + 30);
	r += 40;

	circleUnit newCircle6(("pattern/pattern_4.png"), r, 45, rand() % 30 + 30);
	r += 45;

	circleUnit newCircle7(("pattern/pattern_3.png"), r, 30, rand() % 30 + 35);
	r += 30;

	_circleList.push_back(newCircle1);
	_circleList.push_back(newCircle2);
	_circleList.push_back(newCircle3);
	_circleList.push_back(newCircle4);
	_circleList.push_back(newCircle5);
	_circleList.push_back(newCircle6);
	_circleList.push_back(newCircle7);
}