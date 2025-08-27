#pragma once
#include <math.h>
#include <random>
#include <time.h>

#define PI 3.14153

namespace utl {
	float getAngle(float x1, float y1, float x2, float y2);

	float dist(float x1, float y1, float x2, float y2);

	int randRange(int min, int max);

	float randRange(float min, float max);

	float radToDeg(float radians);

	float degToRad(float degrees);
}