#pragma once

#include "SBase.h"

class SR04 : public SBase {

public:
	SR04()
		:SBase(eSR04)
	{}

	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "SR04 Puis qu'ici-has toute ame\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	string getSceneName() { return "SR04"; }

private:

};