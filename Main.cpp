#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"vertexGenerator.h"
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
		0.02f, 1.0f, 0.0f, 0.0f,
		0.04f, 0.0f, 1.0f, 0.0f
	};

	// Initilising vertex and index buffers
	GLfloat vertices[13 * 6 * NUM_PARTICLES_MAIN] = {};
	GLuint indices[21 * NUM_PARTICLES_MAIN] = {};

	Particle2D* particles = new Particle2D[NUM_PARTICLES_MAIN]{};

	Shader shaderProgram("particle2d.vert", "default.frag");

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);


		//Simulate here

		fillVertices(particles, vertices, indices, NUM_PARTICLES_MAIN, typeData, 4);

		// Generates Vertex Array Object and binds it
		VAO VAO1;
		VAO1.Bind();

		// Generates Vertex Buffer Object and links it to vertices
		VBO VBO1(vertices, sizeof(vertices));

		// Generates Element Buffer Object and links it to indices
		EBO EBO1(indices, sizeof(indices));

		// Links VBO to VAO
		VAO1.LinkAttrib(VBO1, 0, 2, GL_FLOAT, 6 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 6 * sizeof(float), (void*)(2 * sizeof(float)));

		// Unbind all
		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();

		shaderProgram.Activate();

		//Set zoom level here
		glUniform1f(uniID, 0.0f);

		// Bind the VAO
		VAO1.Bind();
	
		glDrawElements(GL_TRIANGLE_STRIP, 21*NUM_PARTICLES_MAIN, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();

		// effectivly reset all the buffers
		VAO1.Delete();
		VBO1.Delete();
		EBO1.Delete();
	}


	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}