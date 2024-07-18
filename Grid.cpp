#include"Grid.h"
#include"GridSection.h"
#include<iostream>

using namespace std;
#include"math.h"

Grid::Grid(int numX, int numY, float size, float maxReach, int cap)
{
	numParticles = 0;
	capacity = cap;
	gridSize = size;
	sizeX = numX;
	sizeY = numY;

	float addedOffset = 1.5f;

	float gridsRadius = maxReach / size + addedOffset;
	int iGridRad = (int) ceil(gridsRadius);

	int numGrid = numX * numY;
	int xPos, yPos;
	float distance;

	GridSection *g1, *g2;

	//Initilising all gridsections

	sections = new GridSection[numGrid];

	//Filling up the near and adjacent sections of seach gridsections
	for (int i = 0; i < numGrid; i++)
	{
		xPos = i % numY;
		yPos = (i - xPos)/numY;
    
		g1 = &sections[i];

		std::cout << xPos << ", " << yPos << std::endl;

		for (int x = (xPos - iGridRad > 0) ? xPos - iGridRad : 0; x < (xPos + iGridRad) && x < numX; x++)
		{
			for (int y = (yPos - iGridRad > 0) ? yPos - iGridRad: 0; y < (yPos + iGridRad) && y < numY; y++)
			{
				distance = sqrtf(powf((float)(xPos - x), 2) + powf((float)(yPos - y), 2));
				if (distance <= gridsRadius + 1.6f && (x != xPos || y != yPos))
				{
					g2 = &sections[x + y * numY];
					g1->addAdjacent(*g2);

					std:cout << "Adjacent added: " << "( " << x << ", " << y << " )" << std::endl;

					if ((xPos == x + 1 || xPos == x - 1 || xPos == x) && (yPos == y + 1 || yPos == y - 1 || yPos == y)) {
						g1->addNear(*g2);
						std::cout << "Near added: " << "( " << x << ", " << y << " )" << std::endl;
					}
				}
			}
		}
		std::cout << "Near: " << g1->nearGrids.size() << std::endl;
		std::cout << "Adjacent: " << g1->adjacentGrids.size() << std::endl;
	}
}

void Grid::insertParticle(Particle& p)
{
	GridSection &gs = sections[(int)(p.x/gridSize) + (int)(p.y/gridSize) * sizeY];
	gs.addParticle(p);
}

int Grid::deleteParticle(int pID, float pX, float pY)
{
	GridSection &gs = sections[(int)pX + (int)pY * sizeY];
	return gs.removeParticle(pID);
}

void Grid::step(float time, float speedLimit)
{
	for (int i = 0; i < sizeX * sizeY; i++)
	{
		sections[i].step(time, speedLimit);
	}
}

void Grid::updateVelocities(float time, float** typeMatrix, forceFunc* forceFuncs)
{
	for (int i = 0; i < sizeX * sizeY; i++)
	{
		sections[i].updateVelocities(time, typeMatrix, forceFuncs);
	}
}

void Grid::handleCollsions(collisionResolver resolver, float* sizes)
{
	for (int i = 0; i < sizeX * sizeY; i++)
	{
		sections[i].handleCollsions(resolver, sizes);
	}
}

void Grid::clear()
{
	for (int i = 0; i < sizeX * sizeY; i++)
	{
		sections[i].clear();
	}
}