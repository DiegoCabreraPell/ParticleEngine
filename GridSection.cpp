#include "GridSection.h"
#include "vector"
using namespace std;

GridSection::GridSection() 
{
	particles = vector<Particle*>();
	adjacentGrids = vector<GridSection*>();
	nearGrids = vector<GridSection*>();
}

void GridSection::addParticle(Particle &p)
{
	particles.push_back(&p);
}


int GridSection::removeParticle(int pID)
{
	for (auto i = particles.begin(); i != particles.end(); i++)
		if ((*i)->ID() == pID) {
			particles.erase(i);
			return 0;
		}
	return 1;
}

void GridSection::addAdjacent(GridSection &gs)
{
	adjacentGrids.push_back(&gs);
}

void GridSection::addNear(GridSection &gs)
{
	nearGrids.push_back(&gs);
}

void GridSection::step(float time, float speedLimit)
{
	float vel, distStep, coeff;
	for (auto i = particles.begin(); i != particles.end(); i++)
	{
		vel = sqrtf(powf((*i)->dx, 2) + powf((*i)->dy, 2));
		distStep = time * speedLimit;
		if (vel > distStep) {
			coeff = distStep / vel;
			(*i)->dx *= coeff;
			(*i)->dy *= coeff;
		}
		(*i)->step(time);
	}
}

void GridSection::updateVelocities(float time, float** typeMatrix, forceFunc*forceFuncs)
{
	float distance, dy, dx, force, nx, ny;

	for (auto i = particles.begin(); i != particles.end(); i++)
	{
		//Calculate particle with other particles in its sector
		for (auto j = i+1; j != particles.end(); j++)
		{
			dy = (*j)->y - (*i)->y;
			dx = (*j)->x - (*i)->x;

			if (dx == 0.0f)
				dx = 0.1f;
			if (dy == 0.0f)
				dy = 0.1f;

			distance = sqrtf(powf(dy, 2) + powf(dx, 2));


			nx = dx / distance;
			ny = dy / distance;

			force = forceFuncs[(*j)->type](distance) * typeMatrix[(*j)->type][(*i)->type] * time;

			(*i)->addDx(nx * force);
			(*i)->addDy(ny * force);

			force = forceFuncs[(*i)->type](distance) * typeMatrix[(*i)->type][(*j)->type] * time;

			(*j)->addDx(-nx * force);
			(*j)->addDy(-ny * force);
		}

		//calculate particle with particles from near sectors
		for (auto sector = nearGrids.begin(); sector != nearGrids.end(); sector++)
		{
			for (auto p = (*sector)->particles.begin(); p != (*sector)->particles.end(); p++)
			{
				dy = (*p)->y - (*i)->y;
				dx = (*p)->x - (*i)->x;

				if (dx == 0.0f)
					dx = 0.1f;
				if (dy == 0.0f)
					dy = 0.1f;

				distance = sqrtf(powf(dy, 2) + powf(dx, 2));

				nx = dx / distance;
				ny = dy / distance;

				force = forceFuncs[(*p)->type](distance) * typeMatrix[(*p)->type][(*i)->type] * time;

				(*i)->addDx(nx * force);
				(*i)->addDy(ny * force);
			}
		}

	}
}

void GridSection::handleCollsions(collisionResolver resolver, float* sizes) 
{
	float dx, dy, distance;

	for (auto i = particles.begin(); i != particles.end(); i++)
	{
		//check for collisions to particles in its sector
		for (auto j = i; j != particles.end(); j++)
		{
			dy = (*i)->y - (*j)->y;
			dx = (*i)->x - (*j)->x;

			if (dx == 0.0f)
				dx = 0.00001;
			if (dy == 0.0f)
				dy = 0.00001;

			distance = sqrtf(powf(dy, 2) + powf(dx, 2)) - sizes[(*i)->type] - sizes[(*j)->type];

			if (distance < 0)
				resolver(**i, **j, distance);
		}

		//checks for collisions with particles in adjacent grids
		for (auto sector = nearGrids.begin(); sector != nearGrids.end(); sector++)
		{
			for (auto p = (*sector)->particles.begin(); p != (*sector)->particles.end(); p++)
			{
				dy = (*i)->y - (*p)->y;
				dx = (*i)->x - (*p)->x;

				if (dx == 0.0f)
					dx = 0.00001;
				if (dy == 0.0f)
					dy = 0.00001;

				distance = sqrtf(powf(dy, 2) + powf(dx, 2)) - sizes[(*i)->type] - sizes[(*p)->type];

				if (distance < 0)
					resolver(**i, **p, distance);
			}
		}
	}
}

void GridSection::clear()
{
	particles.clear();
}