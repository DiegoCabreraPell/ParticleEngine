#ifndef VERTEX_GENERATOR_H
#define VERTEX_GENERATOR_H

#include"particle2DClass.h"
#include<GLFW/glfw3.h>

enum VdataEntry {
	SCALAR,
	R,
	G,
	B,
};

void fillVertices(Particle2D* particles, GLfloat* vertexList, GLuint* indexList,
	int num_particles, GLfloat* dataArr, int dataComps);

#endif
