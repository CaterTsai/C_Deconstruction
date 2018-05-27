#include "DTemple.h"

#pragma region pillarUnit
void DTemple::pillarUnit::update(float delta)
{
}
#pragma endregion

//----------------------------------
void DTemple::update(float delta)
{
	CHECK_START();

	auto pos = _light.getPosition();
	pos += _lightV * delta;
	_light.setPosition(pos);

	if (pos.z > 0 || pos.z < -3000)
	{
		_lightV.z = -_lightV.z;
	}
}

//----------------------------------
void DTemple::draw()
{
	CHECK_START();

	ofPushStyle();
	ofEnableLighting();

	_light.enable();
	{
		for (auto& iter : _pillarMgr)
		{
			ofPushMatrix();
			ofTranslate(iter._pos);
			{
				_pillar.drawFaces();
			}
			ofPopMatrix();
		}
	}
	_light.disable();
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

		pillarUnit left(leftPos, true), right(rightPos, false);
		_pillarMgr.push_back(left);
		_pillarMgr.push_back(right);

		startPos.z -= 600;
	}
}

//----------------------------------
void DTemple::initLight()
{
	ofSetSmoothLighting(true);
	_light.setAmbientColor(ofColor(50, 0, 0));
	_light.setDiffuseColor(ofColor(0, 100, 255));
	_light.setPosition(0, -500, 0);
	_light.setAttenuation(1.0f, 0.000014f, 0.0000001f);
	_lightV.set(0, 0, -200);

}


