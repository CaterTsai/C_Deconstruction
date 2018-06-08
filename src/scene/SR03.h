#pragma once

#include "SBase.h"

class SR03 : public SBase {

public:
	SR03()
		:SBase(eSR03)
	{}

	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "SR03 Quando m'en vo'\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	string getSceneName() { return "SR03"; }

private:

};