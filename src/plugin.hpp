#pragma once
#include <rack.hpp>

using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
// extern Model* modelMyModule;
extern Model* modelVCDualNeuron;
extern Model* modelComparator;
extern Model* modelMultiplier;
extern Model* modelSum;
extern Model* modelDiff;
extern Model* modelNot;
extern Model* modelAbs;
extern Model* modelASR;
extern Model* modelVCSampleAndDelay;
extern Model* modelDAC;
extern Model* modelADC;
extern Model* modelMax;
extern Model* modelPosNegRectifier;
extern Model* modelMin;
extern Model* modelFunction;
extern Model* modelAvg;
extern Model* modelABY;
extern Model* modelOffset;
extern Model* modelClip;
extern Model* modelCtV;
extern Model* modelBlank;

