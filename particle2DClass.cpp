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

void Particle2D::addVelocity(GLfloat dx, GLfloat dy)
{
	vel[0] += dx;
	vel[1] += dy;
}

void Particle2D::setVelocity(GLfloat dx, GLfloat dy)
{
	vel[0] = dx;
	vel[1] = dy;
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