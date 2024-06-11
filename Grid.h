#ifndef GRID_H
#define GRID_H

#include "GridSection.h"
#include "Particle.h

class Grid
{
	int capacity, numParticles;
	GridSection sections[];

	Grid(int numX, int numY, int size, float maxReach);
	void insertParticle(Particle &p);
	Particle* popParticle(int pID);
	Particle* getParticle(int pID);
	int deleteParticle(int pID);
};

#endif 

