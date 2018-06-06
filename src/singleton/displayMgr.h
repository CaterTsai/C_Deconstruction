#pragma once

#include "displayUnit.h"


class displayMgr
{
public:
	displayMgr();
	void setup(string configName = "");
	void displayEachUnit(ofVec2f pos, int height);
	void drawToProjection();

	void enableDisplayControl(int unitID);
	void disableDisplayControl();
	
	void clearDispaly(int unitID);
	void clearAllDisplay();

	void saveConfig(string configName);

	ofRectangle getSize(int unitID);
private:
	void init(string configName);
private:
	bool _isSetup;
	int _ctrlID;

	vector<displayUnit>	_displayList;

//Draw On Unit
public:
	void updateOnUnitBegin(int unitID, bool needClear = true);
	void updateOnUnitEnd(int unitID);
	
//Mouse Event
public:
	void mousePressedFromProjector(int x, int y);
	void mouseDraggedFromProjector(int x, int y);
	void mouseReleasedFromProject(int x, int y);

//-------------------
//Singleton
//-------------------
public:
	static displayMgr* GetInstance();
	static void Destroy();

private:
	static displayMgr *pInstance;
};