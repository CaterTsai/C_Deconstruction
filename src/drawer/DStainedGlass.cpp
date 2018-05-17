#include "DStainedGlass.h"

#pragma region Mask
DStainedGlass::mask::mask(string path, eMaskType type)
	:_type(type)
	, _rV(0.0f)
	, _r(0.0f)
{
	if (!_mask.load(path))
	{
		ofLog(OF_LOG_WARNING, "[DStainedGlass::Mask]Load Mask Failed : " + path);
	}
}

void DStainedGlass::mask::draw(int cx, int cy, int width, int height)
{
	if (!_mask.isAllocated())
	{
		return;
	}

	ofPushStyle();
	ofPushMatrix();
	ofTranslate(cx, cy);
	ofRotateZ(_r);
	{
		float asp = _mask.getWidth() / _mask.getHeight();
		float w = (asp >= 1.0f ? width : height * asp);
		float h = (asp >= 1.0f ? width / asp : height);

		ofSetColor(255);
		_mask.draw(w * -0.5f, h* -0.5f, w, h);
	}
	ofPopMatrix();
	ofPopStyle();
}

void DStainedGlass::mask::setRotate(float rotateV)
{
	_rV = rotateV;
}

//-----------------------------------------
int DStainedGlass::mask::getType()
{
	return _type;
}
#pragma endregion


//-----------------------------------------
void DStainedGlass::update(float delta)
{
	CHECK_START();

	_rotate += _rotateV * delta;
	if (_rotate > 360)
	{
		_rotate -= 360;
	}
	if (_rotate < -360)
	{
		_rotate += 360;
	}

	updateSeed(delta);
	_voronoi.begin();
	{
		ofPushStyle();
		ofSetColor(255);
		ofPushMatrix();
		{
			_img.draw(0, 0, cVoronoiWidth, cVoronoiHeight);
		}
		ofPopMatrix();
		ofPopStyle();
	}
	_voronoi.end();
	_voronoi.update();

	//Draw Layer
	_masker.beginLayer();
	{
		_voronoi.draw();
	}
	_masker.endLayer();

	//Draw Mask
	_masker.beginMask();
	{
		ofClear(0);
		ofSetColor(255);
		_maskMgr[_maskIdx].draw(cVoronoiWidth * 0.5f, cVoronoiHeight * 0.5f, cVoronoiWidth, cVoronoiHeight);
	}
	_masker.endMask();
}

//-----------------------------------------
void DStainedGlass::draw()
{
	CHECK_START();

	ofPushStyle();
	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(_masker.getWidth() * 0.5, _masker.getHeight() * 0.5);
	if (_maskMgr[_maskIdx].getType() == eMaskType::eMaskCircle)
	{
		ofRotateZ(_rotate);
	}
	_masker.draw(_masker.getWidth() * -0.5, _masker.getHeight() * -0.5);
	ofPopMatrix();
	ofPopStyle();
}

//-----------------------------------------
void DStainedGlass::start()
{
	initVoronoi();
	_maskIdx = 0;
	_isStart = true;
}

//-----------------------------------------
void DStainedGlass::stop()
{
	_isStart = false;
	_rotate = 0.0f;
	_rotateV = 0.0f;
}

//-----------------------------------------
void DStainedGlass::trigger(int key)
{
	if (key >= 0 && key < _maskMgr.size())
	{
		_maskIdx = key;
	}

}

//-----------------------------------------
void DStainedGlass::startRotate(float rv)
{
	_rotate = 0.0f;
	_rotateV = rv;
}

//-----------------------------------------
void DStainedGlass::initMask()
{
	_maskMgr.push_back(mask("stainedGlassMask/c_1.jpg", eMaskType::eMaskCircle));
	_maskMgr.push_back(mask("stainedGlassMask/c_2.jpg", eMaskType::eMaskCircle));
	_maskMgr.push_back(mask("stainedGlassMask/c_3.jpg", eMaskType::eMaskCircle));
	_maskMgr.push_back(mask("stainedGlassMask/c_4.jpg", eMaskType::eMaskCircle));
	_maskMgr.push_back(mask("stainedGlassMask/c_5.jpg", eMaskType::eMaskCircle));
	_maskMgr.push_back(mask("stainedGlassMask/c_6.jpg", eMaskType::eMaskCircle));
	_maskMgr.push_back(mask("stainedGlassMask/w_1.jpg", eMaskType::eMaskWindow));
	_maskMgr.push_back(mask("stainedGlassMask/w_2.jpg", eMaskType::eMaskWindow));

}

//-----------------------------------------
void DStainedGlass::initVoronoi()
{
	_voronoi.setup(512, 512);
	setSeed();
}

//-----------------------------------------
void DStainedGlass::setSeed()
{
	_voronoi._seedList.clear();
	ofVec2f v(0, -1);
	v.rotate(30);
	for (int idx_ = 0; idx_ < cVoronoiSeedNum; idx_++)
	{
		_voronoi._seedList.push_back(ofVec2f(rand() % cVoronoiWidth, rand() % cVoronoiHeight));

		if (idx_ % 2 == 0)
		{
			_seedV.push_back(v * ofRandom(5, 10));
		}
		else
		{
			_seedV.push_back(ofVec2f(0));
		}
	}
}

//-----------------------------------------
void DStainedGlass::updateSeed(float delta)
{
	for (int idx_ = 0; idx_ < cVoronoiSeedNum; idx_++)
	{
		_voronoi._seedList[idx_] += _seedV[idx_] * delta;

		//X
		if (_voronoi._seedList[idx_].x < 0)
		{
			_voronoi._seedList[idx_].x += cVoronoiWidth;
		}
		else if (_voronoi._seedList[idx_].x >= cVoronoiWidth)
		{
			_voronoi._seedList[idx_].x -= cVoronoiWidth;
		}

		//Y
		if (_voronoi._seedList[idx_].y < 0)
		{
			_voronoi._seedList[idx_].y += cVoronoiHeight;
		}
		else if (_voronoi._seedList[idx_].y >= cVoronoiHeight)
		{
			_voronoi._seedList[idx_].y -= cVoronoiHeight;
		}
	}
}
