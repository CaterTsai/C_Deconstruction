#include "displayMgr.h"
#include "ofxXmlSettings.h"

#pragma region Basic
//------------------------------
displayMgr::displayMgr()
	:_isSetup(false)
	,_ctrlID(-1)
{
}

//------------------------------
void displayMgr::setup(string configName)
{
	if (_isSetup)
	{
		ofLog(OF_LOG_ERROR, "[displayMgr::setup]setup already");
		return;
	}
	init(configName);

	_isSetup = true;
}


//------------------------------
void displayMgr::displayEachUnit(ofVec2f pos, int height)
{
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(pos);
	{
		int drawPosX = 0;
		for (int i = 0; i < _displayList.size(); i++)
		{
			auto rect = _displayList[i].getSize();
			int h = height;
			int w = height * rect.width / rect.height;
			_displayList[i].drawCanvas(drawPosX, 0, w, h);

			ofNoFill();
			ofSetColor(255);
			ofDrawRectangle(drawPosX, 0, w, h);

			drawPosX += w;
		}
	}
	ofPopMatrix();
	ofPopStyle();
}

//------------------------------
void displayMgr::drawToProjection()
{
	ofPushStyle();
	for (auto& unit : _displayList)
	{
		unit.drawOnProjection();
	}
	ofPopStyle();

	//Display Ctrl point
	if (_ctrlID != -1)
	{
		_displayList.at(_ctrlID).drawCtrlPos();
	}
}

//------------------------------
void displayMgr::enableDisplayControl(int unitID)
{
	_ctrlID = unitID;
}

//------------------------------
void displayMgr::disableDisplayControl()
{
	_ctrlID = -1;
}

//------------------------------
void displayMgr::clearDispaly(int unitID)
{
	updateOnUnitBegin(unitID);
	ofClear(0);
	updateOnUnitEnd(unitID);
}

//------------------------------
void displayMgr::clearAllDisplay()
{
	for (int i = 0; i < cDisplayNum; i++)
	{
		clearDispaly(i);
	}
}

//------------------------------
void displayMgr::saveConfig(string configName)
{
	ofxXmlSettings xml;

	for (int i = 0; i < cDisplayNum; i++)
	{
		auto rect = _displayList[i].getSize();
		xml.addTag("display");
		xml.pushTag("display", i);
		xml.addValue("displayW", rect.width);
		xml.addValue("displayH", rect.height);

		for (int j = 0; j < 4; j++)
		{
			auto ctrlPos = _displayList.at(i).getCtrlPos(j);
			xml.addTag("ctrlPos_" + ofToString(j + 1));
			xml.pushTag("ctrlPos_" + ofToString(j + 1));

			xml.addValue("x", ctrlPos.x);
			xml.addValue("y", ctrlPos.y);

			xml.popTag();
		}
		xml.popTag();
	}
	if (xml.saveFile(configName))
	{
		ofLog(OF_LOG_NOTICE, "[displayMgr::saveConfig]Save config success");
	}
	else
	{
		ofLog(OF_LOG_NOTICE, "[displayMgr::saveConfig]Save config failed");
	}
}

//------------------------------
ofRectangle displayMgr::getSize(int unitID)
{
	return _displayList[unitID].getSize();
}

//------------------------------
void displayMgr::init(string configName)
{
	ofxXmlSettings xml;
	if (!xml.loadFile(configName))
	{
		ofLog(OF_LOG_ERROR, "[displayMgr::init]Load config failed :" + configName);
	}

	stDisplayParam param;
	if (xml.getNumTags("display") != cDisplayNum)
	{
		ofLog(OF_LOG_ERROR, "[displayMgr::init]wrong square number");
	}

	for (int i = 0; i < cDisplayNum; i++)
	{	
		xml.pushTag("display", i);
		displayUnit newUnit;
		int displayW = xml.getValue("displayW", 100, 0);
		int displayH = xml.getValue("displayH", 100, 0);

		for (int j = 0; j < 4; j++)
		{
			int x = xml.getValue("ctrlPos_" + ofToString(j + 1) + ":x", 0, 0);
			int y = xml.getValue("ctrlPos_" + ofToString(j + 1) + ":y", 0, 0);
			param.ctrlPos[j].set(x, y);
		}
		
		newUnit.setup(displayW, displayH, param);
		_displayList.push_back(newUnit);
		xml.popTag();
	}

}
#pragma endregion

#pragma region On Unit
//------------------------------
void displayMgr::updateOnUnitBegin(int unitID, bool needClear)
{
	if (!_isSetup)
	{
		return;
	}

	_displayList.at(unitID).drawBegin(needClear);
}

//------------------------------
void displayMgr::updateOnUnitEnd(int unitID)
{
	if (!_isSetup)
	{
		return;
	}
	_displayList.at(unitID).drawEnd();
}

#pragma endregion

#pragma region Mouse

//------------------------------
void displayMgr::mousePressedFromProjector(int x, int y)
{
	if (_ctrlID != -1)
	{
		_displayList.at(_ctrlID).mousePress(x, y);
	}
}

//------------------------------
void displayMgr::mouseDraggedFromProjector(int x, int y)
{
	if (_ctrlID != -1)
	{
		_displayList.at(_ctrlID).mouseDrag(x, y);
	}
}

//------------------------------
void displayMgr::mouseReleasedFromProject(int x, int y)
{
	if (_ctrlID != -1)
	{
		_displayList.at(_ctrlID).mouseRelease(x, y);
	}
}
#pragma endregion

#pragma region Singleton
//--------------------------------------------------------------
displayMgr* displayMgr::pInstance = 0;
displayMgr* displayMgr::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new displayMgr();
	}
	return pInstance;
}

//--------------------------------------------------------------
void displayMgr::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}
#pragma endregion




