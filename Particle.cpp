#include"Particle.h"

Particle::Particle(int pID, int pType) {
	id = pID;
	type = pType;
	x = 0.0f;
	y = 0.0f;
	dx = 0.0f;
	dy = 0.0f;
}

Particle::Particle(int pID, int pType, float pX, float pY) {
	id = pID;
	type = pType;
	x = pX;
	y = pY;
	dx = 0.0f;
	dy = 0.0f;
}

Particle::Particle(int pID, int pType, float pX, float pY, float Dx, float Dy) {
	id = pID;
	type = pType;
	x = pX;
	y = pY;
	dx = Dx;
	dy = Dy;
}

void Particle::addX(float pX) {
	x += pX;
}
void Particle::addY(float pY) {
	y += pY;
}

void Particle::addDx(float vX) {
	dx += vX;
}

void Particle::addDy(float vY) {
	dy += vY;
}

int Particle::ID() {
	return id;
}

void Particle::step(float s) {
	addX(dx);
	addY(dy);
}
