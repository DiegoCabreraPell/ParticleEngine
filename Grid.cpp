#include"Grid.h"
#include"GridSection.h"

using namespace std;
#include"math.h"

Grid::Grid(int numX, int numY, int size, float maxReach, int cap)
{
	numParticles = 0;
	capacity = cap;
	gridSize = size;
	sizeX = numX;
	sizeY = numY;

	float gridsRadius = (float) ceil(maxReach / (float)size);

	int numGrid = numX * numY;
	int xPos, yPos;
	float distance;

	GridSection g1, g2;

	//Initilising all gridsections
	*sections = new GridSection[numGrid];
	for (int i = 0; i < numX; i++)
	{
		*(sections[i]) = GridSection();
	}

	//Filling up the near and adjacent sections of seach gridsections
	for (int i = 0; i < numX; i++)
	{
		xPos = i % numY;
		yPos = i - xPos;

		g1 = *(sections[i]);

		for (int x = xPos-gridsRadius; x < xPos+gridsRadius; x++)
		{
			for (int y = yPos - gridsRadius; y < yPos + gridsRadius; y++)
			{
				if (x >= 0 && y >= 0 && x != xPos && y != yPos)
				{
					distance = sqrtf(powf(xPos - x, 2) + powf(yPos - y, 2));
					if (distance <= gridsRadius)
					{
						g2 = *(sections[x + y * numY]);
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
	GridSection gs = *sections[(int)p.x + (int)p.y * sizeY];
	gs.addParticle(p);
}

int Grid::deleteParticle(int pID, float pX, float pY)
{
	GridSection gs = *sections[(int)pX + (int)pY * sizeY];
	gs.removeParticle(pID);
}