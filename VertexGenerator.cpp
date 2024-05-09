#include"vertexGenerator.h"
#include<GLFW/glfw3.h>

#define NUM_POINTS_ON_CIRCLE 12

void fillVertices(Particle2D* particles, GLfloat* vertexList, GLuint* indexList,
	int num_particles, GLfloat* dataArr, int dataComps)
{
	//unit vectors for a circle split by 12 vertices
	GLfloat unitVecs[12][2] = {
		{0.0f,1.0f},
		{0.5f,0.866f},
		{0.866f, 0.5f},
		//second quarter
		{1.0f,0.0f},
		{0.866f, -0.5f},
		{0.5f,-0.866f},
		//third quarter
		{-1.0f,0.0f},
		{-0.5f,-0.866f},
		{-0.866f, -0.5f},
		//fourth quarter
		{-1.0f,0.0f},
		{-0.866f, 0.5f},
		{-0.5f,0.866f}
	};

	Particle2D& particle = *particles;

	int vIndex = 0;
	int iIndex = 0;

	unsigned short type;
	GLfloat scalar, r, g, b;
	int dataOffset;

	for (int pIndex = 0; pIndex < num_particles; pIndex++)
	{
		particle = particles[pIndex];

		type = particle.type;
		dataOffset = type * dataComps;
		scalar = dataArr[dataOffset + SCALAR];
		r = dataArr[dataOffset + R];
		g = dataArr[dataOffset + G];
		b = dataArr[dataOffset + B];

		//Setting vertices total: 13 per particle

		//Putting down center vertex
		vertexList[vIndex++] = particle.pos[0];
		vertexList[vIndex++] = particle.pos[1];
		vertexList[vIndex++] = r;
		vertexList[vIndex++] = g;
		vertexList[vIndex++] = b;
		vertexList[vIndex++] = 1.0f;

		//Putting all other points to the vertex array
		for (int i = 0; i < NUM_POINTS_ON_CIRCLE; i++)
		{
			vertexList[vIndex++] = particle.pos[0] + scalar * unitVecs[i][0];
			vertexList[vIndex++] = particle.pos[1] + scalar * unitVecs[i][1];
			vertexList[vIndex++] = r;
			vertexList[vIndex++] = g;
			vertexList[vIndex++] = b;
			vertexList[vIndex++] = 0.0f;
		}

		//Setting index pattern total: 21 per particle

		for (int j = 0; j < 4; j++)
		{
			indexList[iIndex++] = j * 3 + 1;
			indexList[iIndex++] = j * 3 + 2;
			indexList[iIndex++] = 0;
			indexList[iIndex++] = j * 3 + 3;
			indexList[iIndex++] = j * 3 + 4;
		}

		//Preimitive restart
		indexList[iIndex++] = 0xffff;
	}
}
