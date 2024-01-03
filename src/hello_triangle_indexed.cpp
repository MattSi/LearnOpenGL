#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include "hello_triangle_indexed.h"
#include "cyMatrix.h"
#include "cyGL.h"
#include "cyTriMesh.h"


static void resize(GLFWwindow* window, int width, int height);
static void process_input(GLFWwindow* window);

static const unsigned int SCR_WIDTH = 800;
static const unsigned int SCR_HEIGHT = 600;

static cyGLSLProgram program;
static GLuint program_id;
static GLuint shader_yellow;
static GLuint shader_green;

static void CompileProgram() {
	bool result;
	if (!(result = program.BuildFiles("hello_triangle_indexed.vert", "hello_triangle_indexed.frag"))) {
		fprintf(stderr, "Error: program compiliation failed.\n");
		exit(1);
	}
	program_id = program.GetID();
	program.Bind();
}

int hello_triangle_indexed(int argc, char* argv[]) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	bool result;
	result = program.BuildFiles("hello_triangle_indexed.vert", "hello_triangle_indexed.frag");
	if (!result) {
		fprintf(stderr, "Error: program 1 compiliation failed.\n");
		exit(1);
	}
	shader_yellow = program.GetID();

	result = program.BuildFiles("hello_triangle_indexed.vert", "hello_triangle_indexed_2.frag");
	CompileProgram();
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
		//0.6f,0.8f,0.9f,

	};

	float triangle1[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
	};

	float triangle2[] = {
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f ,  // top left 
		0.6f,0.8f,0.9f,
	};

	

	unsigned int indices[] = {
		0,1,3, // First triangle
		1,0,2  // Second triangle
	};

	
	unsigned int VBOs[2], VAOs[2], EBO;
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	// first triangle setup

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// second triangle setup
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	

	

	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		process_input(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_green);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//

		glUseProgram(shader_yellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(program_id);

	glfwTerminate();
	return 0;
}

static void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

static void resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}