#ifndef GRIDSECTION_H
#define GRIDSECTION_H

#include"Particle.h"
#include<vector>

using namespace std;

class GridSection
{
	vector<Particle> particles;
	vector<GridSection> adjacentGrids;
	vector<GridSection> nearGrids;

public:
	GridSection();

	void addParticle(Particle p);
	int removeParticle(int pID);

	void addAdjacent(GridSection gs);
	void addNear(GridSection gs);
	void step(float time);
	void updateVelocities(float time, float** typeMatrix, float (**forceFuncs)(float));
};

#endif
