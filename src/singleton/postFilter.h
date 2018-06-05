#pragma once

#include "../constParameter.h"
#include "ofxPostProcessing.h"

enum ePostFilterType
{
	ePostBloom = 0
	,ePostBloomTwo
	,ePostNoiseWarp
	,ePostZoomBlur
	,ePostKaleidoscope
	,ePostEdge
	,ePostPixel
	,ePostRGBShift
	,ePostToon
};

class postFilter
{
public:
	void init(int index, int w, int h);
	void filterEnable(int index, ePostFilterType type);
	void filterEnable(int index, ePostFilterType type, bool isEnable);
	void disableAll();
private:
	bool _isInit;

public:
	array<ofxPostProcessing, cDisplayNum> _postMgr;
//-------------------
//Singleton
//-------------------
private:
	postFilter()
		:_isInit(false)
	{};
	~postFilter()
	{
		postFilter::Destroy();
	}
	postFilter(postFilter const&);
	void operator=(postFilter const&);

public:
	static postFilter* GetInstance();
	static void Destroy();

private:
	static postFilter *pInstance;
};