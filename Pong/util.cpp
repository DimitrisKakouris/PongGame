#include "util.h"
#include <random>
#include <xiosbase>
#include <time.h>


float rand0to1()
{
	return rand() / (float)RAND_MAX;

}

float randomHeight()
{
    float Temp = 0.0f;
    srand(time(NULL));
    Temp = rand() % 300+300;
    return  Temp;
}

float randomHeightforball()
{
    float Temp = 0.0f;
    srand(time(NULL));
    Temp = rand() % 300 + 200;
    return  Temp;
}


float randomWidth()
{
    float Temp = 0.0f;
    srand(time(NULL));
    Temp = rand() % 200+100;
    return  Temp;
}

float randoPlin1to1() {
    int a = -1;
    int b = 1;

    srand(time(NULL));
    int r = rand() % 2;

    if (r == 0) return a;
    else        return b;

}