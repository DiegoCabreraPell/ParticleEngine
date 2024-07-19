#ifndef GPSIM_CLASS_H
#define GPSIM_CLASS_H
#include"Particle.h"
#include"Grid.h"
#include"SimTypes.h"


void DEFAULTCOLLISIONRESOLVER(Particle &p1, Particle &p2, float distance);

class ParticleSimulation
{
protected:
	//simulation area information
	int pixelWidth, pixelHeight;
	float aspectRatio;

	//simulation meta information
	int numTypes, gridSize;
	float speedLimit, energyDampener, universalX, universalY;
	float* typeSizes, *typeWeights;
	collisionResolver resolver;

	//Particle information
	int numParticles, maxParticles;
	Particle** particles;

	vector<int> freeIDs;

	float** typeMat;
	forceFunc defaultForceFunc, *typeForceFuncs;

	Grid* grid;
	 
public:
	ParticleSimulation(int pHeight, int pWidth, int mParticles, int nTypes, float maxCmptDist, float gSize, forceFunc dForceFunc);
	void setSpeedLimit(float limit);
	int getFreeID();
	void step(float timeStep);
	void setCollisionResolver(collisionResolver res);

	Particle* getParticle(int pID);
	int removeParticle(int pID);
	int addParticle(float x, float y, int type, float dx, float dy);
	int addParticle(float x, float y, int type);
	int addParticle(int type);
	int setPWeight(int type, float weight);
	int setPSize(int type, float radius);
	const float* getPWeights() const;
	const float* getPSizes() const;
	int getNumParticles() const;
	bool isFull() const;
	Particle** particleList() const;
	void setTypeInteractionCoefficient(int t1, int t2, float coeff);
	void setDampener(float c);
	void setUniversalForce(float dx, float dy);
};

#endif

