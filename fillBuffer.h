#ifndef FILL_BUFFER_H
#define FILL_BUFFER_H

#include"Particle.h"
#include<GLFW/glfw3.h>

enum VdataEntry {
	SCALAR,
	R,
	G,
	B,
};

void fillVertices(Particle** particles, GLfloat* vertexList, int num_particles, GLfloat* dataArr, int dataComps);

void fillIndices(GLuint* indexList, int numParticles);

#endif
