#ifndef GRID_H
#define GRID_H

#include "GridSection.h"
#include "Particle.h"
#include <array>

class Grid
{
	int capacity, numParticles, gridSize, sizeX, sizeY;
	GridSection **sections;

public:
	Grid(int numX, int numY, float size, float maxReach, int cap);
	void insertParticle(Particle &p);
	int deleteParticle(int pID, float pX, float pY);
	void step(float time);
	void updateVelocities(float time, float** typeMatrix, forceFunc* forceFuncs);
	void handleCollsions(void (*resolver)(Particle, Particle), float* sizes);
};

#endif 

