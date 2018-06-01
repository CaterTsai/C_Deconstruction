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

const int cTemplePillarRowNum = 8;

const int cPortraitUnitSize = 2000;
const int cPortraitMaskSize = 200;
const int cPortraitPhotoSize = 1000;
const int cPortraitMaskToPhoto = 5;
const int cPortraitMaskThreshold = 50;

