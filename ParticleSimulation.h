#ifndef GPSIM_CLASS_H
#define GPSIM_CLASS_H
#include"Particle.h"
#include"Grid.h"
#include"SimTypes.h"


void DEFAULTCOLLISIONRESOLVER(Particle, Particle);

float DEFAULTFORCEFUNCTION(float);

class ParticleSimulation
{
protected:
	//simulation area information
	int pixelWidth, pixelHeight;
	float aspectRatio;

	//simulation meta information
	int numTypes, gridSize;
	float speedLimit;
	float* typeSizes, *typeWeights;
	collisionResolver resolver;

	//Particle information
	int numParticles, maxParticles;
	Particle** particles;

	vector<int> freeIDs;

	float** typeMat;
	forceFunc* typeForceFuncs;

	Grid* grid;
	 
public:
	ParticleSimulation(int pHeight, int pWidth, int mParticles, int numTypes, float maxCmptDist, float gSize);
	void setSpeedLimit(float limit);
	int getFreeID();
	void step(float timeStep);
	void setCollisionResolver(void (*res)(Particle, Particle));

	Particle* getParticle(int pID);
	int removeParticle(int pID);
	int addParticle(float x, float y, int type, float dx, float dy);
	int addParticle(float x, float y, int type);
	int addParticle(int type);
	int setPWeight(int type, float weight);
	int setPSize(int type, float radius);
	const float* getPWeights();
	const float* getPSizes();
	int getNumParticles();
	bool isFull() const;
	Particle** particleList();
};

#endif

