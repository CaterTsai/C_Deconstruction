#pragma once

#include "../constParameter.h"

//DStainedGlass
const int cVoronoiSeedNum = 200;
const int cVoronoiWidth = 400;
const int cVoronoiHeight = 400;
const float cStainedRotateMin = 0.0f;
const float cStainedRotateMax = 180.0f;

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
const float cBreezEmitterSlow = 1.0f;
const float cBreezEmitterFast = 0.2f;
const int cBreezEmitterNumMin = 1;
const int cBreezEmitterNumMax = 5;
const ofColor cBreezBaseColor(0, 75, 129);

const int cCloudImgNum = 4;
const int cCloudColorHueMin = 180;
const int cCloudColorHueMax = 220;
const int cCloudImageBaseWidth = 1000;
const int cCloudParticalMax = 100;
const int cCloudUnitMax = 30;
const int cCloudPEmitterSlow = 3.0f;
const int cCloudPEmitterFast = 0.5f;
const int cCloudCEmitterSlow = 4.0f;
const int cCloudCEmitterFast = 2.0f;
const ofColor cCloudBaseColor(0, 203, 207);

const int cTemplePillarRowNum = 8;
const ofColor cTempleLightBaseColor(235, 0, 41);

const int cPortraitUnitSize = 1000;
const int cPortraitMaskSize = 200;
const int cPortraitPhotoSize = 1000;
const int cPortraitMaskToPhoto = 5;
const int cPortraitMaskThreshold = 150;
const int cPortraitCircleRadius = cPortraitPhotoSize * 0.4f;

//DTail
const ofRectangle cTailRange = ofRectangle(0, 0, cWindowWidth, cWindowHeight);
const int cTailWidthLimit = 2;
const float cTailParticalSizeMin = 2.0f;
const float cTailParticalSizeMax = 4.0f;
const float cTailParticalSpeedMin = 50.0f;
const float cTailParticalSpeedMax = 150.0f;
const float cTailFlowFieldsMin = 50.0f;
const float cTailFlowFieldsMax = 150.0f;
const int cTailEmitterNumMin = 1;
const int cTailEmitterNumMax = 5;
const float cTailEmitterTSlow = 1.0;
const float cTailEmitterTFast = 0.2;

//DLife
const int cWorldWidth = 150;
const int cWorldHeight = 150;
