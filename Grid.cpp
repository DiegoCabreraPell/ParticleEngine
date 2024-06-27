#include"Grid.h"
#include"GridSection.h"

using namespace std;
#include"math.h"

Grid::Grid(int numX, int numY, float size, float maxReach, int cap)
{
	numParticles = 0;
	capacity = cap;
	gridSize = size;
	sizeX = numX;
	sizeY = numY;

	float gridsRadius = maxReach / size;
	int iGridRad = (int) ceil(gridsRadius);

	int numGrid = numX * numY;
	int xPos, yPos;
	float distance;

	GridSection g1, g2;

	//Initilising all gridsections
	sections = new GridSection[numGrid];

	//Filling up the near and adjacent sections of seach gridsections
	for (int i = 0; i < numGrid; i++)
	{
		xPos = i % numY;
		yPos = i - xPos;

		g1 = sections[i];

		for (int x = xPos- iGridRad; x < xPos+ iGridRad; x++)
		{
			for (int y = yPos - iGridRad; y < yPos + iGridRad; y++)
			{
				if (x >= 0 && y >= 0 && x != xPos && y != yPos)
				{
					distance = sqrtf(powf((float)(xPos - x), 2) + powf((float)(yPos - y), 2));
					if (distance <= gridsRadius)
					{
						g2 = sections[x + y * numY];
						g1.addAdjacent(g2);

						if (xPos == x + 1 || xPos == x - 1 || yPos == y + 1 || yPos == y - 1) {
							g1.addNear(g2);
						}
					}
				}
			}
		}
	}
}

void Grid::insertParticle(Particle& p)
{
	GridSection gs = sections[(int)p.x + (int)p.y * sizeY];
	gs.addParticle(p);
}

int Grid::deleteParticle(int pID, float pX, float pY)
{
	GridSection gs = sections[(int)pX + (int)pY * sizeY];
	return gs.removeParticle(pID);
}

void Grid::step(float time)
{
	for (int i = 0; i < sizeX * sizeY; i++)
	{
		sections[i].step(time);
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