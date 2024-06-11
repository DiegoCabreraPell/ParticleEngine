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

	GridSection();

	void addParticle(Particle p);
	int removeParticle(int pID);

	void addAdjacent(GridSection gs);
	void addNear(GridSection gs);
};

#endif
