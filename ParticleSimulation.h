#ifndef GPSIM_CLASS_H
#define GPSIM_CLASS_H
#include"Particle.h"

void (*DEFAULTCOLLISIONRESOLVER) (Particle, Particle);

class ParticleSimulation
{
protected:
	//simulation area information
	int pixelWidth, pixelHeight;
	float aspectRatio;

	//simulation meta information
	int numTypes, gridSize;
	float speedLimit, defaultTimeStep;
	float* typeData, interactionMatrix;
	void (*collisionResolver) (Particle, Particle);

	//Particle information
	int numParticles, maxParticles;
	//particles

public:
	ParticleSimulation(int pHeight, int pWidth, int mParticles);
	void setSpeedLimit(float limit);
	int getFreeID();
	void setDefaultTimeStep();
	void step(float timeStep);
	void step();
	void setCollisionResolver(void (*res)(Particle, Particle));

	Particle getParticle(int pID);
	void removeParticle(int pID);
	void addParticle(float x, float y, int type, float dx, float dy);
	void addParticle(float x, float y, int type);
	void addParticle(int type);
	bool isFull();
};

#endif

