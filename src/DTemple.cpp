#include "DTemple.h"

#pragma region lightUnit
//----------------------------------
void DTemple::lightUnit::update(float delta)
{
	if (!_isOn)
	{
		return;
	}
	_animMove.update(delta);
	_animColor.update(delta);
	_light.setDiffuseColor(_animColor.getCurrentColor());
	_light.setPosition(_animMove.getCurrentPosition());

	if (_isOn && _animColor.hasFinishedAnimating() && _animColor.getPercentDone() == 1.0f)
	{
		auto c = _animColor.getCurrentColor();
		if (_isOn && c.r == 0 && c.g == 0 && c.b == 0)
		{
			_isOn = false;
		}
	}
}

//----------------------------------
void DTemple::lightUnit::lightTo(float t, ofColor target)
{
	_isOn = true;
	_animColor.setDuration(t);
	_animColor.animateTo(target);
}


//----------------------------------
void DTemple::lightUnit::lightOff(float t)
{
	_animColor.setDuration(t);
	_animColor.animateTo(ofColor(0));
}

//----------------------------------
void DTemple::lightUnit::toggle(float t, ofColor target)
{
	if (_isOn)
	{
		lightOff(t);
	}
	else
	{
		lightTo(t, target);
	}
}

//----------------------------------
void DTemple::lightUnit::startMove(float t, ofVec3f start, ofVec3f end)
{
	_animMove.setPosition(start);
	_animMove.setDuration(t);
	_animMove.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
	_animMove.animateTo(end);
}

//----------------------------------
void DTemple::lightUnit::stopMove()
{
	_animMove.pause();
}


#pragma endregion


//----------------------------------
void DTemple::update(float delta)
{
	CHECK_START();

	for (auto& iter : _lightMgr)
	{
		iter.update(delta);
	}
}

//----------------------------------
void DTemple::draw()
{
	CHECK_START();

	////Debug
	//for (auto& iter : _lightMgr)
	//{
	//	ofSetColor(iter._light.getDiffuseColor());
	//	ofDrawSphere(iter._light.getPosition(), 50);
	//}

	ofPushStyle();
	ofEnableLighting();
	for (auto& iter : _lightMgr) {
		if (iter._isOn)
		{
			iter._light.enable();
		}		
	}
	{
		for (auto& iter : _pillarMgr)
		{
			ofPushMatrix();
			ofTranslate(iter);
			{
				_pillar.drawFaces();
			}
			ofPopMatrix();
		}
	}
	for (auto& iter : _lightMgr)
	{
		if (iter._isOn)
		{
			iter._light.disable();
		}
	}
	ofDisableLighting();
	ofPopStyle();
}

//----------------------------------
void DTemple::start()
{
	_isStart = true;
	initLight();
	ofEnableDepthTest();
}

//----------------------------------
void DTemple::stop()
{
	_isStart = false;
	ofDisableDepthTest();
}

//----------------------------------
void DTemple::trigger(int key)
{
	if (key >= 0 && key <= 7)
	{
		_lightMgr[key].toggle(5.0f, ofColor(0, 100, 255));
		_lightMgr[key].startMove(3.0f, ofVec3f(0, 0, _lightMgr[key]._light.getPosition().z), ofVec3f(0, -1500, _lightMgr[key]._light.getPosition().z));
	}
	else if (key == ' ')
	{
		ofColor c = _lightMgr[0]._light.getDiffuseColor();
		float h = c.getHueAngle() + ofRandom(30, 60);
		c.setHueAngle(h);
		_lightMgr[0].lightTo(5.0f, c);
	}

}

//----------------------------------
void DTemple::loadPillar()
{
	_pillar.loadModel("OldColumn/OldColumn.obj", 20);
	_pillar.setPosition(0, 0, 0);
	_pillar.setScale(1.5, 1.5, 1.5);
	auto& helper = _pillar.getMeshHelper(0);
	helper.material.setShininess(20);
	helper.material.setAmbientColor(ofColor(20, 0, 0));

	ofVec3f startPos(0, 0, 0);
	for (int i = 0; i < cTemplePillarRowNum; i++)
	{
		ofVec3f leftPos, rightPos;
		leftPos = rightPos = startPos;
		leftPos.x -= 500;
		rightPos.x += 500;
		_pillarMgr.push_back(leftPos);
		_pillarMgr.push_back(rightPos);

		startPos.z -= 600;
	}
}

//----------------------------------
void DTemple::initLight()
{
	ofSetSmoothLighting(true);

	ofVec3f startPos(0, 0, 0);
	for (int i = 0; i < cTemplePillarRowNum; i++)
	{
		ofVec3f pos = startPos;		

		_lightMgr[i]._light.setDiffuseColor(ofColor(0));
		_lightMgr[i]._light.setPosition(pos);
		_lightMgr[i]._light.setAttenuation(1.0f, 0.000007f, 0.000001f);
		startPos.z -= 600;

	}
}

