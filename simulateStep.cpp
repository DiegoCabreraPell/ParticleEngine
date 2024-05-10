#include"simulateStep.h"
#include<array>
#include<vector>
#include<cmath>

void simulateStep(Particle2D* particles, int numParticles, GLfloat* typeData, int dataComps, GLfloat** typeMatrix)
{
	//Subdivide simulation area into sectors
	//Reduces checks necccesary
	std::array<std::vector<Particle2D*>, 25> sectors;

	std::vector<Particle2D*>* pVec;
	Particle2D* particle;

	int pixelX, pixelY, xIndex, yIndex;

	//Pushing particles to their correct sector
	for (int i = 0; i < numParticles; i++)
	{
		particle = particles+i;

		pixelX = 400 * particle->pos[0] + 400;
		pixelY = 400 * particle->pos[1] + 400;

		xIndex = floor(pixelX / (800 / 5));
		yIndex = floor(pixelY / (800 / 5));

		sectors[5 * yIndex + xIndex].push_back(particle);
	}

	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			
		}
	}
}