#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "interpolation.h"
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
	if (!(result = program.BuildFiles("p6_interpolation.vert", "p6_interpolation.frag"))) {
		fprintf(stderr, "Error: program compiliation failed.\n");
		exit(1);
	}
	program_id = program.GetID();
	program.Bind();
}


int interpolation(int argc, char* argv[]) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL P6 Shader", NULL, NULL);

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

	float colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};

	unsigned int VAO, VBO[2];
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	GLuint pos = glGetAttribLocation(program_id, "pos");
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(pos);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	GLuint clr = glGetAttribLocation(program_id, "clr");
	glVertexAttribPointer(clr, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(clr);


	float offset = 0.5f;
	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		glBindVertexArray(VAO);
		//offset += 0.001f;
		if (offset > 1.0f) {
			offset = -0.5f;
		}
		GLint offsetLocation = glGetUniformLocation(program_id, "offset");
		glUniform1f(offsetLocation, offset);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(2, VBO);
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