#include "Global.h"
double randomDouble(double min, double max)
{
	return 1.0 * rand() / RAND_MAX * (max - min) + min;
}