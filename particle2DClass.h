#ifndef PARTICLE_CLASS_H
#define PARTICLE_CLASS_H

#include<GLFW/glfw3.h>

class Particle2D
{
public:
	unsigned short int type;
	GLfloat* pos;
	GLfloat* vel;

	Particle2D();
	Particle2D(GLfloat x, GLfloat y, unsigned short _type);
	void addVelocity(GLfloat dx, GLfloat dy);
	void setVelocity(GLfloat dx, GLfloat dy);
	void setPos(GLfloat _x, GLfloat _y);
	void step();
	~Particle2D();
};

#endif
