#include "B2.h"
#include "Base.h"
B2 b2 = B2();

float randInterval(float min, float max){
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}
