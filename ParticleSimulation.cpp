#include"ParticleSimulation.h"
#include"Particle.h"
#include"SimTypes.h"

void DEFAULTCOLLISIONRESOLVER(Particle &p1, Particle &p2, float distance)
{
	float dy, dx, ddx, ddy, nx, ny, force;

	dx = p1.x - p2.x;
	dy = p1.y - p2.y;

	ddx = p1.dx - p2.dx;
	ddy = p1.dy - p2.dy;
	
	force = sqrtf(powf(ddx, 2) + powf(ddy, 2));

	nx = dx / distance;
	ny = dy / distance;
	
	p1.addX(- nx * distance / 2);
	p1.addY(- ny * distance / 2);

	p2.addY(ny * distance / 2);
	p2.addY(ny * distance / 2);

	p1.addDx(-nx * force);
	p1.addDy(-ny * force);
	
	p2.addDx(nx * force);
	p2.addDy(ny * force);

}

ParticleSimulation::ParticleSimulation(int pHeight, int pWidth, int mParticles, int nTypes, float maxCmptDist, float gSize, forceFunc dForceFunc)
{
	int numX = (int) round((float)pWidth/gSize);
	int numY = (int) round((float)pHeight/gSize);
	grid = new Grid(numX, numY, gSize, maxCmptDist, mParticles);

	aspectRatio = (float)pHeight / (float)pWidth;
	resolver = DEFAULTCOLLISIONRESOLVER;
	gridSize = gSize;

	pixelWidth = pWidth;
	pixelHeight = pHeight;
	numTypes = nTypes;
	maxParticles = mParticles;
	numParticles = 0;
	speedLimit = 100.0f / 60.0f;

	typeMat = new float*[nTypes];

	for (int i = 0; i < nTypes; i++)
		typeMat[i] = new float[nTypes] {0.0f};

	defaultForceFunc = dForceFunc;

	typeForceFuncs = new forceFunc[nTypes]{defaultForceFunc};
	typeSizes = new float[nTypes] {gSize / 5};
	typeWeights = new float[nTypes] {1.0f};

	//Initialising free particle id vector and particle address array
	particles = new Particle * [maxParticles]();
	freeIDs = vector<int>(maxParticles);
	for (int i = 0; i < maxParticles; i++)
	{
		particles[i] = NULL;
		freeIDs.push_back(i);
	}
}

void ParticleSimulation::setSpeedLimit(float limit) {
	speedLimit = limit;
}

int ParticleSimulation::getFreeID() 
{
	if (freeIDs.empty())
		return -1;
	else
	{
		int id = freeIDs.back();
		freeIDs.pop_back();
		return id;
	}
}

void ParticleSimulation::step(float timeStep) 
{
	//update velocity
	grid->updateVelocities(timeStep, typeMat, typeForceFuncs);
	
	//update position
	grid->step(timeStep);
	
	//detect and resolve collisions
	grid->handleCollsions(resolver, typeSizes);

	//Refreshing the grid positions
	grid->clear();

	int count = numParticles;
	int ind = 0;
	Particle* p;
	while (count > 0)
	{
		p = particles[ind++];
		if (p != NULL)
		{
			grid->insertParticle(*p);
			count -= 1;
		}
	}
}

void ParticleSimulation::setCollisionResolver(collisionResolver res) {
	resolver = res;
}

Particle* ParticleSimulation::getParticle(int pID) 
{
	if (pID >= 0 || pID < maxParticles)
	{
		if (particles[pID] != NULL)
			return particles[pID];
	}

	return NULL;
}

int ParticleSimulation::removeParticle(int pID)
{
	if (pID >= 0 || pID < maxParticles)
	{
		if (particles[pID] == NULL)
			return -1;

		Particle p = *particles[pID];

		grid->deleteParticle(pID, p.x,p.y);
		delete particles[pID];
		particles[pID] = NULL;

		numParticles -= 1;
	}
	return -1;
}

int ParticleSimulation::addParticle(float x, float y, int type, float dx, float dy) 
{
	int id = getFreeID();
	if (id != -1)
	{
		particles[id] = new Particle(id, type, x, y, dx, dy);
		grid->insertParticle(*(particles[id]));
		numParticles += 1;
		return 0;
	}
	return -1;
}

int ParticleSimulation::addParticle(float x, float y, int type) 
{
	return addParticle(x, y, type, 0.0f, 0.0f);
}

int ParticleSimulation::addParticle(int type) 
{
	return addParticle(0.0f, 0.0f, type, 0.0f, 0.0f);
}

int ParticleSimulation::setPWeight(int type, float weight)
{
	if (type >= numTypes || type < 0)
		return 1;

	typeWeights[type] = weight;
	return 0;
}

int ParticleSimulation::setPSize(int type, float radius)
{
	if (type >= numTypes || type < 0)
		return 1;

	typeSizes[type] = radius;
	return 0;
}

const float* ParticleSimulation::getPWeights() const
{
	return typeWeights;
}

const float* ParticleSimulation::getPSizes() const
{
	return typeSizes;
}

int ParticleSimulation::getNumParticles() const
{
	return numParticles;
}

bool ParticleSimulation::isFull() const 
{
	if (numParticles == maxParticles)
	{
		return true;
	}
	else {
		return false;
	}
}

Particle** ParticleSimulation::particleList () const
{
	return particles;
}

