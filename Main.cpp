#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"fillBuffer.h"
#include"particle2DClass.h"

#define NUM_PARTICLES_MAIN 2

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Particle Simulation", NULL, NULL);

	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//openGL environment
	gladLoadGL();

	glViewport(0, 0, 800, 800);

	glPrimitiveRestartIndex(0xffff);
	glEnable(GL_PRIMITIVE_RESTART);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//creating type data
	GLfloat typeData[] = {
		0.08f, 0.0f, 1.0f, 0.0f,
		0.08f, 0.0f, 0.0f, 1.0f
	};

	Particle2D* particles = new Particle2D[NUM_PARTICLES_MAIN]{ {0.0f,0.0f,0}, {0.04f, 0.0f, 1} };

	// Initilising vertex and index buffers
	GLfloat vertices[13 * 6 * NUM_PARTICLES_MAIN] = {};
	fillVertices(particles, vertices, NUM_PARTICLES_MAIN, typeData, 4);

	GLuint indices[21 * NUM_PARTICLES_MAIN] = {};
	fillIndices(indices, NUM_PARTICLES_MAIN);

	Shader shaderProgram("particle2d.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;

	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		
		shaderProgram.Activate();
		glUniform1f(uniID, 0.0f);

		VAO1.Bind();
		VBO VBO1(vertices, sizeof(vertices));
		EBO1.Bind();

		//Linking layouts
		VAO1.LinkAttrib(VBO1, 0, 2, GL_FLOAT, 6 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 6 * sizeof(float), (void*)(2 * sizeof(float)));

		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();

		//Draw call
		VAO1.Bind();
		glDrawElements(GL_TRIANGLE_STRIP, 21 * NUM_PARTICLES_MAIN, GL_UNSIGNED_INT, 0);
		VAO1.Unbind();

		//deleting old VBO
		VBO1.Delete();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}