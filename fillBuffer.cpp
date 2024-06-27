#include"fillBuffer.h"
#include<GLFW/glfw3.h>


#define NUM_POINTS_ON_CIRCLE 12

void fillVertices(Particle** particles, GLfloat* vertexList, int num_particles, GLfloat* dataArr, int dataComps)
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
		{0.0f,-1.0f},
		{-0.5f,-0.866f},
		{-0.866f, -0.5f},
		//fourth quarter
		{-1.0f,0.0f},
		{-0.866f, 0.5f},
		{-0.5f,0.866f}
	};

	Particle* particle;

	int vIndex = 0;
	int iIndex = 0;

	unsigned short type;
	GLfloat scalar, r, g, b;
	int dataOffset;

	for (int pIndex = 0; pIndex < num_particles; pIndex++)
	{
		particle = particles[pIndex];
		if (particle != NULL)
		{
			type = particle->type;
			dataOffset = type * dataComps;
			scalar = dataArr[dataOffset + SCALAR];
			r = dataArr[dataOffset + R];
			g = dataArr[dataOffset + G];
			b = dataArr[dataOffset + B];

			//Setting vertices total: 13 per particle @ 6 comps per particle

			//Putting down center vertex
			vertexList[vIndex++] = particle->x / 400.0f - 1.0f;
			vertexList[vIndex++] = particle->y / 400.0f - 1.0f;;
			vertexList[vIndex++] = r;
			vertexList[vIndex++] = g;
			vertexList[vIndex++] = b;
			vertexList[vIndex++] = 1.0f;

			//Putting all other points to the vertex array
			for (int i = 0; i < NUM_POINTS_ON_CIRCLE; i++)
			{
				vertexList[vIndex++] = (particle->x / 400.0f - 1.0f) + scalar * unitVecs[i][0];
				vertexList[vIndex++] = (particle->y / 400.0f - 1.0f) + scalar * unitVecs[i][1];
				vertexList[vIndex++] = r;
				vertexList[vIndex++] = g;
				vertexList[vIndex++] = b;
				vertexList[vIndex++] = 0.0f;
			}
		}
	}
}

void fillIndices(GLuint* indexList, int numParticles) 
{
	int indexOffset;
	int iIndex = 0;
	for (int i = 0; i < numParticles; i++)
	{
		//Setting index pattern total: 21 per particle

		indexOffset = i * 13;

		for (int j = 0; j < NUM_POINTS_ON_CIRCLE/3 - 1; j++)
		{
			indexList[iIndex++] = indexOffset + j * 3 + 1;
			indexList[iIndex++] = indexOffset + j * 3 + 2;
			indexList[iIndex++] = indexOffset + 0;
			indexList[iIndex++] = indexOffset + j * 3 + 3;
			indexList[iIndex++] = indexOffset + j * 3 + 4;
		}

		indexList[iIndex++] = indexOffset + 10;
		indexList[iIndex++] = indexOffset + 11;
		indexList[iIndex++] = indexOffset + 0;
		indexList[iIndex++] = indexOffset + 12;
		indexList[iIndex++] = indexOffset + 1;

		//Primitive restart
		indexList[iIndex++] = 0xffff;
	}
}
