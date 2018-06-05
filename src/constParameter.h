#pragma once

#include "ofMain.h"

//#define PROJECTION_MODE

static string ws2s(wstring wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, 0);
	string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, 0);
	return strTo;

}

//--------------------------------------------------------------
static wstring s2ws(const string & str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

//--------------
//Window
const int cWindowWidth = 1920;
const int cWindowHeight = 1080;

const int cProjectionWindowWidth = 1920;
const int cProjectionWindowHeight = 1080;

const int cViewCanvasWidth = 1024;
const int cViewCanvasHeight = 1024;

const int cViewWindowWidth = 1024;
const int cViewWindowHeight = 1024;

//--------------
//Display Manager
const int cCtrlPointNum = 4;

const int cCtrlPointCircleRadius = cProjectionWindowHeight * 0.02;
const int cCtrlPointMaxDist = cCtrlPointCircleRadius;
const int cDisplayNum = 3;

enum eDisplayType : int
{
	eFront = 0
	, eObject
	, eBack
};


//--------------
//Video Mgr
enum eVideoType : int
{
	eVideoBIntro = 0
	,eVideoCIntro
	,eVideoRIntro
	,eVideoMIntro
	, eVideoMonika
	, eVideoNum
};