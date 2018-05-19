#include "DEgyptianVertical.h"

#pragma region verticalUnit
//-----------------------------------
DEgyptianVertical::verticalUnit::verticalUnit(int x)
	:_pos(x, 0)
	, _startChange(false)
{
	_yv = ofRandom(30, 100) * (rand() % 2 == 1 ? 1 : -1);
	startMove();
	generatorText();
	_animAlpha.reset(0.0f);
	_animAlpha.setDuration(2.0f);
}

//-----------------------------------
void DEgyptianVertical::verticalUnit::update(float delta)
{
	_animAlpha.update(delta);

	if (_isMove)
	{
		_pos.y += _yv * delta;
		if (_yv > 0)
		{
			if (_pos.y > cEgyptianVerticalHeight)
			{
				_pos.y = _pos.y - (cEgyptianVerticalTextNum * cEgyptianVerticalUnitHeight);
			}
		}
		else
		{
			if (_pos.y < -cEgyptianVerticalUnitHeight)
			{
				_pos.y = _pos.y + (cEgyptianVerticalTextNum * cEgyptianVerticalUnitHeight);
			}
		}
	}
	

	if (_startChange)
	{
		changeText();
	}
}

//-----------------------------------
void DEgyptianVertical::verticalUnit::draw(ofxTrueTypeFontUC & font)
{
	ofPushStyle();
	ofSetColor(255, _animAlpha.getCurrentValue());

	ofVec2f drawPos = _pos;

	//Down
	for (int i = 0; i < cEgyptianVerticalTextNum; i++)
	{
		auto box = font.getStringBoundingBox(_text[i], 0, 0);

		ofPushMatrix();
		ofTranslate(drawPos.x, (drawPos.y + cEgyptianVerticalUnitHeight * 0.5));
		font.drawString(_text[i], box.width * -0.5, box.height * 0.5);
		ofPopMatrix();

		drawPos.y += cEgyptianVerticalUnitHeight;
		if (drawPos.y > cEgyptianVerticalHeight)
		{
			break;
		}
	}

	//Up
	drawPos = _pos;
	for (int i = cEgyptianVerticalTextNum - 1; i >= 0; i--)
	{
		drawPos.y -= cEgyptianVerticalUnitHeight;

		auto box = font.getStringBoundingBox(_text[i], 0, 0);
		ofPushMatrix();
		ofTranslate(drawPos.x, (drawPos.y + cEgyptianVerticalUnitHeight * 0.5));
		font.drawString(_text[i], box.width * -0.5, box.height * 0.5);
		ofPopMatrix();

		if (drawPos.y < -cEgyptianVerticalUnitHeight)
		{
			break;
		}
	}

	ofPopStyle();
}

//-----------------------------------
void DEgyptianVertical::verticalUnit::in()
{
	_animAlpha.animateTo(255.0f);
}

//-----------------------------------
void DEgyptianVertical::verticalUnit::out()
{
	_animAlpha.animateTo(0.0f);
}

//-----------------------------------
void DEgyptianVertical::verticalUnit::toggle()
{
	if (_animAlpha.isAnimating())
	{
		if (_animAlpha.getDirection() > 0)
		{
			out();
		}
		else
		{
			in();
		}
	}
	else
	{
		if (_animAlpha.getCurrentValue() == 0.0f)
		{
			in();
		}
		else
		{
			out();
		}
	}
}

//-----------------------------------
void DEgyptianVertical::verticalUnit::startChange()
{
	for (auto& iter : _changeIdx)
	{
		iter = (rand() % 10 < 2);
	}
	_startChange = true;
}

//-----------------------------------
void DEgyptianVertical::verticalUnit::stopChange()
{
	for (auto& iter : _changeIdx)
	{
		iter = false;
	}
	_startChange = false;
}

//-----------------------------------
void DEgyptianVertical::verticalUnit::startMove()
{
	_isMove = true;
}

//-----------------------------------
void DEgyptianVertical::verticalUnit::stopMove()
{
	_isMove = false;
}

//-----------------------------------
void DEgyptianVertical::verticalUnit::generatorText()
{
	for (int i = 0; i < cEgyptianVerticalTextNum; i++)
	{
		wstring ws(2, L' s');
		ws[0] = 55308;
		ws[1] = cEgyptianUnicodeMin + rand() % (cEgyptianUnicodeMax - cEgyptianUnicodeMin);
		_text[i] = ws2s(ws);
	}
}

//-----------------------------------
void DEgyptianVertical::verticalUnit::changeText()
{
	for (int i = 0; i < cEgyptianVerticalTextNum; i++)
	{
		if (_changeIdx[i])
		{
			wstring ws(2, L' s');
			ws[0] = 55308;
			ws[1] = cEgyptianUnicodeMin + rand() % (cEgyptianUnicodeMax - cEgyptianUnicodeMin);
			_text[i] = ws2s(ws);
		}
	}
}
#pragma endregion

//-----------------------------------
void DEgyptianVertical::update(float delta)
{
	CHECK_START();

	for (auto& iter : _vUnitMgr)
	{
		iter.update(delta);
	}

}

//-----------------------------------
void DEgyptianVertical::draw()
{
	CHECK_START();

	for (auto& iter : _vUnitMgr)
	{
		iter.draw(_font);
	}
}

//-----------------------------------
void DEgyptianVertical::start()
{
	if (_font.isLoaded())
	{
		_isStart = true;
		initVertiaclUnit();
	}

}

//-----------------------------------
void DEgyptianVertical::stop()
{
	_isStart = false;
}

//-----------------------------------
void DEgyptianVertical::trigger(int key)
{
	_vUnitMgr[key].toggle();
}

//-----------------------------------
void DEgyptianVertical::loadFont()
{
	_font.setGlobalDpi(72);
	if (!_font.load("fonts/font2.ttf", cEgyptianFontSize))
	{
		ofLog(OF_LOG_ERROR, "[DEgyptianVertical::loadFont]Can't load fonts");
	}

}

//-----------------------------------
void DEgyptianVertical::initVertiaclUnit()
{

	float posX = cEgyptianVerticalUnitWidth * 0.5f;
	_vUnitMgr.push_back(verticalUnit(posX + cEgyptianVerticalUnitWidth * 1));
	_vUnitMgr.push_back(verticalUnit(posX + cEgyptianVerticalUnitWidth * 2));
	_vUnitMgr.push_back(verticalUnit(posX + cEgyptianVerticalUnitWidth * 3));
	_vUnitMgr.push_back(verticalUnit(posX + cEgyptianVerticalUnitWidth * 4));
	_vUnitMgr.push_back(verticalUnit(posX + cEgyptianVerticalUnitWidth * 5));

	posX = cWindowWidth - cEgyptianVerticalUnitWidth * 0.5f;
	_vUnitMgr.push_back(verticalUnit(posX + cEgyptianVerticalUnitWidth * -1));
	_vUnitMgr.push_back(verticalUnit(posX + cEgyptianVerticalUnitWidth * -2));
	_vUnitMgr.push_back(verticalUnit(posX + cEgyptianVerticalUnitWidth * -3));
	_vUnitMgr.push_back(verticalUnit(posX + cEgyptianVerticalUnitWidth * -4));
	_vUnitMgr.push_back(verticalUnit(posX + cEgyptianVerticalUnitWidth * -5));
}




