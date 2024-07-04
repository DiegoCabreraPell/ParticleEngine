#ifndef GRIDSECTION_H
#define GRIDSECTION_H

#include"Particle.h"
#include<vector>
#include "SimTypes.h"

using namespace std;

class GridSection
{
	vector<Particle*> particles;
	vector<GridSection> adjacentGrids;
	vector<GridSection> nearGrids;

public:
	GridSection();

	void addParticle(Particle &p);
	int removeParticle(int pID);

	void addAdjacent(GridSection &gs);
	void addNear(GridSection &gs);
	void step(float time, float speedLimit);
	void updateVelocities(float time, float** typeMatrix, forceFunc* foreFuncs);
	void handleCollsions(collisionResolver resolver, float* sizes);
	void clear();
};

#endif
