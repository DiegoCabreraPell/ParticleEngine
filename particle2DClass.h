#ifndef PARTICLE_CLASS_H
#define PARTICLE_CLASS_H

#include<GLFW/glfw3.h>

class Particle2D
{
public:
	unsigned short int type;
	GLfloat* pos;
	GLfloat* vel;

	Particle2D(GLfloat x, GLfloat y, unsigned short _type);
	void addVelocity(GLfloat* dV);
	void step();
	~Particle2D();
};

#endif
