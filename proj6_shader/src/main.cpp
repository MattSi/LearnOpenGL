#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include "hello_triangle.h"
#include "cyMatrix.h"
#include "cyGL.h"
#include "cyTriMesh.h"


static void resize(GLFWwindow* window, int width, int height);
static void process_input(GLFWwindow* window);

static const unsigned int SCR_WIDTH = 800;
static const unsigned int SCR_HEIGHT = 600;

static cyGLSLProgram program;
static GLuint program_id;

static void CompileProgram() {
	bool result;
	if (!(result = program.BuildFiles("hello_triangle.vert", "hello_triangle.frag"))) {
		fprintf(stderr, "Error: program compiliation failed.\n");
		exit(1);
	}
	program_id = program.GetID();
	program.Bind();
}

int main(int argc, char* argv[]) {
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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	CompileProgram();

	float vertices[] = {
		 -0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top  
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Tell OpenGL how it should interpret vertex data(per vertex attribute)
	// The first parameter specifies which vertex attribute we want to configure, 
	//		in vertex shader, layout(location=0)
	//      this sets the location vertex attribute to 0 since we want to pass data to this vertex attribute, we pass in 0
	// The second parameter specifies the size of the vertex attribute, The vertex attribute is vec3, so that it's composed of 3 values.
	// 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		glUseProgram(program_id);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
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
