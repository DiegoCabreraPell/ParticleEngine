#include"particle2DClass.h"

Particle2D::Particle2D()
{
	pos = new GLfloat[2]{ 0,0 };
	vel = new GLfloat[2]{ 0, 0 };
	type = 0;
}

Particle2D::Particle2D(GLfloat x, GLfloat y, unsigned short _type)
{
	pos = new GLfloat[2]{x,y};
	vel = new GLfloat[2] {0, 0};
	type = _type;
}

void Particle2D::addVelocity(GLfloat* dV)
{
	vel[0] += dV[0];
	vel[1] += dV[1];
}

void Particle2D::addVelocity(GLfloat* dV)
{
	vel[0] += dV[0];
	vel[1] += dV[1];
}
void Particle2D::setVelocity(GLfloat* v)
{
	vel[0] = v[0];
	vel[1] = v[1];
}
void Particle2D::setPos(GLfloat _x, GLfloat _y)
{
	pos[0] = _x;
	pos[1] = _y;
}

void Particle2D::step()
{
	pos[0] += vel[0];
	pos[1] += vel[1];
}

Particle2D::~Particle2D()
{
	delete pos;
	delete vel;
}