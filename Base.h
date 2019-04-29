#pragma once
#include <memory>
#include <Box2D/Box2D.h>
#include "SimulationStructs.h"
#include "Constants.h"
#include "B2.h"
extern B2 b2;

template <typename T> int sgn(T val){
	return (T(0) < val) - (val < T(0));
}

float randInterval(float min, float max);

