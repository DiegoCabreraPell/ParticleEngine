#ifndef GPSIM_CLASS_H
#define GPSIM_CLASS_H
#include"Particle.h"
#include"Grid.h"

void (*DEFAULTCOLLISIONRESOLVER) (Particle, Particle);

class ParticleSimulation
{
protected:
	//simulation area information
	int pixelWidth, pixelHeight;
	float aspectRatio;

	//simulation meta information
	int numTypes, gridSize;
	float speedLimit;
	float* typeData, interactionMatrix;
	void (*collisionResolver) (Particle, Particle);

	//Particle information
	int numParticles, maxParticles;
	Particle** particles;

	vector<int> freeIDs;


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
	bool isFull() const;
};

#endif

