#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <tuple>
using namespace std;
typedef tuple<double, double, double, double> Observation;
double randomDouble(double min = -RAND_MAX, double max = RAND_MAX);
#define PI 3.14