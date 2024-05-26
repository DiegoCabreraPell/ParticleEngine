#include"simulateStep.h"
#include<array>
#include<vector>
#include<cmath>

GLfloat distanceScalar(GLfloat x)
{
	return -(x - 0.2) / (0.2 + 100 * x * x);
}

void simulateVelocities(std::vector<Particle2D*> sector, std::vector<std::vector<Particle2D*>> neighbors, GLfloat* typeMatrix, int numTypes)
{
	// n * m checks to to other sectors where n is the #particles in the sector and m is the #particles in the other sector
	// (n^2+n)/2 checks within the sector

	Particle2D* particle;
	GLfloat distance, x, y, magnitude, dx, dy, scaledUnitX, scaledUnitY;

	while (!sector.empty())
	{
		particle = sector.back();
		sector.pop_back();

		x = particle->pos[0];
		y = particle->pos[1];

		//simulate with other particles in the sector
		for (auto &pOther : sector)
		{
			dx = pOther->pos[0] - x;
			dy = pOther->pos[1] - y;
			distance = sqrtf(pow(dx, 2) + pow(dy, 2))-0.016f;

			if (distance == 0)
			{
				distance = -0.016f;
				dx = 0.01f;
				dy = 0.01f;
			}
			if (distance < 0)
			{
				scaledUnitX = dx / distance * 0.1;
				scaledUnitY = dy / distance * 0.1;

				particle->addVelocity(
					scaledUnitX,
					scaledUnitY
				);

				pOther->addVelocity(
					-scaledUnitX,
					-scaledUnitY
				);
			}
			else if (distance<=0.2f)
			{
				magnitude = distanceScalar(distance+0.016);

				scaledUnitX = dx / distance * magnitude;
				scaledUnitY = dy / distance * magnitude;

				particle->addVelocity(
					scaledUnitX * typeMatrix[particle->type * numTypes + pOther->type],
					scaledUnitY * typeMatrix[particle->type * numTypes + pOther->type]
				);

				pOther->addVelocity(
					-scaledUnitX * typeMatrix[pOther->type * numTypes + particle->type],
					-scaledUnitY * typeMatrix[pOther->type * numTypes + particle->type]
				);
			}
		}

		for (auto &outSector : neighbors)
		{
			for (auto& pOut : outSector)
			{
				dx = pOut->pos[0] - x;
				dy = pOut->pos[1] - y;
				distance = sqrtf(pow(dx, 2) + pow(dy, 2));
				if (distance <= 0.2)
				{
					magnitude = distanceScalar(distance);

					scaledUnitX = dx / distance * magnitude;
					scaledUnitY = dy / distance * magnitude;

					particle->addVelocity(
						scaledUnitX * typeMatrix[particle->type * numTypes + pOut->type],
						scaledUnitY * typeMatrix[particle->type * numTypes + pOut->type]
					);
				}
			}
		}
	}
}

void simulateStep(Particle2D** particles, int numParticles, GLfloat* typeData, int dataComps, GLfloat* typeMatrix, int numTypes)
{
	//Subdivide simulation area into sectors
	//Reduces checks necccesary
	std::array<std::vector<Particle2D*>, 25> sectors;

	std::vector<Particle2D*>* pVec;
	Particle2D* particle;

	int pixelX, pixelY, xIndex, yIndex;
	std::vector<std::vector<Particle2D*>> neighbors;


	//Pushing particles to their correct sector
	for (int i = 0; i < numParticles; i++)
	{
		particle = *(particles+i);

		pixelX = 400 * particle->pos[0] + 400;
		pixelY = 400 * particle->pos[1] + 400;

		xIndex = (int)(pixelX / (800 / 5));
		yIndex = (int)(pixelY / (800 / 5));

		if (yIndex == 5)
			yIndex = 4;
		if (xIndex == 5)
			xIndex = 4;

		sectors[5 * yIndex + xIndex].push_back(particle);
	}

	//Stepping through each sector and running the simulation
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			//orthogonal neighbors
			if (x != 0)
			{
				neighbors.push_back(sectors[5 * y + x - 1]);
			}
			
			if (x != 4)
			{
				neighbors.push_back(sectors[5 * y + x + 1]);
			}
			
			if (y != 0)
			{
				neighbors.push_back(sectors[5 * (y - 1) + x]);
			}
			
			if (y != 4)
			{
				neighbors.push_back(sectors[5 * (y + 1) + x]);
			}
			
			//diagonal neighbors
			if (x != 0 && y != 0)
			{
				neighbors.push_back(sectors[5 * (y - 1) + x - 1]);
			}
			
			if (x != 0 && y != 4)
			{
				neighbors.push_back(sectors[5 * (y + 1) + x - 1]);
			}
			
			if (x != 4 && y != 0)
			{
				neighbors.push_back(sectors[5 * (y - 1) + x + 1]);
			}
			
			if (x != 4 && y != 4)
			{
				neighbors.push_back(sectors[5 * (y + 1) + x + 1]);
			}

			//Simulate across neighboors and the sector of the particle
			simulateVelocities(sectors[5 * y + x], neighbors, typeMatrix, numTypes);
			neighbors.clear();
		}
	}

	GLfloat dPos;

	for (int i = 0; i < numParticles; i++)
	{
		dPos = sqrtf(pow(particles[i]->vel[0], 2) + pow(particles[i]->vel[1], 2));
		//speed limit
		if (dPos > 0.005)
			particles[i]->setVelocity(particles[i]->vel[0] / dPos * 0.005, particles[i]->vel[1] / dPos * 0.005);
		
		particles[i]->step();
		if (particles[i]->pos[0] >= 1.0)
		{
			particles[i]->setPos(0.999f, particles[i]->pos[1]);
			particles[i]->setVelocity(0.0f, particles[i]->vel[1]);
		}
		if (particles[i]->pos[0] <= -1.0)
		{
			particles[i]->setPos(-0.999f, particles[i]->pos[1]);
			particles[i]->setVelocity(0.0f,particles[i]->vel[1]);
		}
		if (particles[i]->pos[1] >= 1.0)
		{
			particles[i]->setPos(particles[i]->pos[0], 0.999f);
			particles[i]->setVelocity(particles[i]->vel[0], 0.0f);
		}
		if (particles[i]->pos[1] <= -1.0)
		{
			particles[i]->setPos(particles[i]->pos[0], -0.999f);
			particles[i]->setVelocity(particles[i]->vel[0], 0.0f);
		}

	}
}