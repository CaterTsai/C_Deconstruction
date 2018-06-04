#pragma once

#include "../constParameter.h"

const int cVoronoiSeedNum = 200;
const int cVoronoiWidth = 512;
const int cVoronoiHeight = 512;

const int cEgyptianFontSize = 120;
const int cEgyptianUnicodePrecode = 55308;
const int cEgyptianUnicodeMin = 56321;
const int cEgyptianUnicodeMax = 57311;

const int cEgyptianVerticalHeight = cWindowHeight;
const int cEgyptianVerticalUnitHeight = cEgyptianFontSize * 0.8f;
const int cEgyptianVerticalUnitWidth = cEgyptianVerticalUnitHeight * 1.2;
const int cEgyptianVerticalTextNum = 11;// static_cast<int>(cWindowHeight / (float)cEgyptianVerticalUnitHeight);

const int cFieldRows = 20;
const int cFieldCols = 50;
const ofRectangle cBreezRange = ofRectangle(0, 0, cWindowWidth, cWindowHeight);
const float cBreezParticalSpeedMin = 100.0f;
const float cBreezParticalSpeedMax = 500.0f;
const float cBreezParticalSizeMin = 5.0f;
const float cBreezParticalSizeMax = 20.0f;

const int cCloudImgNum = 4;
const int cCloudColorHueMin = 180;
const int cCloudColorHueMax = 220;
const int cCloudImageBaseWidth = 1000;
const int cCloudParticalMax = 100;
const int cCloudUnitMax = 30;

const int cTemplePillarRowNum = 8;

const int cPortraitUnitSize = 1000;
const int cPortraitMaskSize = 200;
const int cPortraitPhotoSize = 1000;
const int cPortraitMaskToPhoto = 5;
const int cPortraitMaskThreshold = 150;
const int cPortraitCircleRadius = cPortraitPhotoSize * 0.4f;

//DTail

//DLife
const int cWorldWidth = 150;
const int cWorldHeight = 150;

//DMandelbrotSet
const int cDMSCanvasWidth = 1024;
const int cDMSCanvasHeight = 1024;
const int cDMSMaximunCheck = 500;
const float cDMSZoomMax = 100000.0;
const int cDMSColorPatternNum = 6;
const int cDMSCenterNum = 15;
const pair<double, double> cDMSRealPartRange(-1.5, 1.5);
const pair<double, double> cDMSImaginePartRange(-1.5, 1.5);

