#include"particle2DClass.h"

Particle2D::Particle2D(GLfloat x, GLfloat y, unsigned short _type)
{
	pos = new GLfloat[2]{x,y};
	vel = new GLfloat[2] {0, 0};
	type = _type;
}

void Particle2D::addVelocity(GLfloat* dV)
{
	vel[0] = vel[0] + dV[0];
	vel[1] = vel[1] + dV[1];
}

void Particle2D::step()
{
	pos[0] = pos[0] + vel[0];
	pos[1] = pos[1] + vel[1];
}

Particle2D::~Particle2D()
{
	delete pos;
	delete vel;
}