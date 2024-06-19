#include "GridSection.h"
#include "vector"

using namespace std;

GridSection::GridSection() 
{
	particles = vector<Particle>();
	adjacentGrids = vector<GridSection>();
	nearGrids = vector<GridSection>();
}

void GridSection::addParticle(Particle p)
{
	particles.push_back(p);
}


int GridSection::removeParticle(int pID)
{
	for (auto i = particles.begin(); i != particles.end(); i++)
		if ((*i).ID() == pID) {
			particles.erase(i);
			return 0;
		}
	return 1;
}

void GridSection::addAdjacent(GridSection gs)
{
	adjacentGrids.push_back(gs);
}

void GridSection::addNear(GridSection gs)
{
	nearGrids.push_back(gs);
}

void GridSection::step(float time)
{
	for (auto i = particles.begin(); i != particles.end(); i++)
		i->step(time);
}