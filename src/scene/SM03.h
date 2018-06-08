#pragma once

#include "SBase.h"

class SM03 : public SBase {

public:
	SM03()
		:SBase(eSM03)
	{}

	void drawMsg(ofVec2f pos) override {
		ostringstream ss;
		ss << "SM03 Sora\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	string getSceneName() { return "SM03"; }

private:

};