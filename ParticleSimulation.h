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
};

#endif

