#ifndef PARTICLE_CLASS_H
#define PARTICLE_CLASS_H

class Particle2D
{
public:
	unsigned short int type;
	float* pos;
	float* vel;

	Particle2D(float x, float y, unsigned short _type);
	void addVelocity(float* dV);
	void step();
	~Particle2D();
};

#endif
