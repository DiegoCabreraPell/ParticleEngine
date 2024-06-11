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

	GridSection(int numX, int numY, int size, float maxReach);

	void addParticle(Particle p);
	void removeParticle(Particle p);

	void addAdjacent(GridSection gs);
	void addNear(GridSection gs);

	~GridSection();
};

#endif
