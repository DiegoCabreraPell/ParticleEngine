#ifndef PARTICLE_CLASS_H
#define PARTICLE_CLASS_H

class Particle
{
private:
	int id;

public:
	int type;

	float x, y, dx, dy;

	Particle(int pID, int pType);
	Particle(int pID, int pType, float pX, float pY);
	Particle(int pID, int pType, float pX, float pY, float Dx, float Dy);

	void addX(float pX);
	void addY(float pY);

	void addDx(float vX);
	void addDy(float vY);

	int ID();

	void step(float s);
};

#endif
