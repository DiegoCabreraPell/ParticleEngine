#ifndef GRID_H
#define GRID_H

#include "GridSection.h"
#include "Particle.h

class Grid
{
	int capacity, numParticles;
	GridSection sections[];

	Grid();
	void insertParticle(Particle &p);
	void removeParticle(int pID);
	Particle getParticle(int pID);
	void deleteParticle(int pID);
	~Grid();
};

#endif 

