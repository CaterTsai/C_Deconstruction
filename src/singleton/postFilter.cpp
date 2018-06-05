#include "postFilter.h"

//-------------------------------------
void postFilter::init(int index, int w, int h)
{
	_postMgr[index].init(w, h);

	_postMgr[index].createPass<BloomPass>()->setEnabled(false);
	_postMgr[index].createPass<BloomPass>()->setEnabled(false);
	_postMgr[index].createPass<NoiseWarpPass>()->setEnabled(false);
	_postMgr[index].createPass<ZoomBlurPass>()->setEnabled(false);
	_postMgr[index].createPass<KaleidoscopePass>()->setEnabled(false);
	_postMgr[index].createPass<EdgePass>()->setEnabled(false);
	_postMgr[index].createPass<PixelatePass>()->setEnabled(false);
	_postMgr[index].createPass<RGBShiftPass>()->setEnabled(false);
	_postMgr[index].createPass<ToonPass>()->setEnabled(false);

	_postMgr[index].setFlip(true);

}

//-------------------------------------
void postFilter::filterEnable(int index, ePostFilterType type)
{
	auto isEnable = !_postMgr[index][(int)type]->getEnabled();
	_postMgr[index][(int)type]->setEnabled(isEnable);
}

//-------------------------------------
void postFilter::filterEnable(int index, ePostFilterType type, bool isEnable)
{
	_postMgr[index][(int)type]->setEnabled(isEnable);
}

//-------------------------------------
void postFilter::disableAll()
{
	for (int i = 0; i < _postMgr.size(); i++)
	{
		for (int j = 0; j < _postMgr[i].size(); j++)
		{
			_postMgr[i][j]->disable();
		}
	}
}


#pragma region Singleton
//--------------------------------------------------------------
postFilter* postFilter::pInstance = 0;
postFilter* postFilter::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new postFilter();
	}
	return pInstance;
}

//--------------------------------------------------------------
void postFilter::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}
#pragma endregion




