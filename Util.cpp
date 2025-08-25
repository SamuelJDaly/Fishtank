#include "Util.h"

float utl::getAngle(float x1, float y1, float x2, float y2)
{
	//Get the angle between two points
	return  atan2f(y2 - y1, x2 - x1);
}

float utl::dist(float x1, float y1, float x2, float y2)
{
	//Get the distance between two points
	return sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
}

int utl::randRange(int min, int max)
{
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

float utl::randRange(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}
