#pragma once
#include <math.h>
#include <random>
#include <time.h>

namespace utl {
	float getAngle(float x1, float y1, float x2, float y2);

	float dist(float x1, float y1, float x2, float y2);

	int randRange(int min, int max);

	float randRange(float min, float max);
}