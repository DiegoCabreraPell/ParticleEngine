#ifndef GRID_H
#define GRID_H

#include "GridSection.h"
#include "Particle.h"
#include <array>
#include"SimTypes.h"

class Grid
{
	int capacity, numParticles, sizeX, sizeY;
	GridSection *sections;
	float gridSize;
public:
	Grid(int numX, int numY, float size, float maxReach, int cap);
	void insertParticle(Particle &p);
	int deleteParticle(int pID, float pX, float pY);
	void step(float time, float speedLimit);
	void updateVelocities(float time, float** typeMatrix, forceFunc* forceFuncs);
	void handleCollsions(collisionResolver resolver, float* sizes);
	void clear();
};

#endif 

