#include <bits/stdc++.h>
using namespace std;
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "camera.h"
#include "shader.h"
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

bool show = false;
bool t= false;
bool different =false;

// timing
float deltaTime = 0.0f;  // time between current frame and last frame
float lastFrame = 0.0f;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// camera
Camera camera(glm::vec3(2.0f, 2.0f, 10.0f));
void key_callback(GLFWwindow *window, int key, int scancode, int action,
				  int mods) {
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		show = !show;
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	    t = !t;
}

void check(){
	if(different)
	{
		different = false;
	}
}

int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "invalid arguement ";
		return 0;
	}
	int n = atoi(argv[1]);

	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	GLFWwindow *window =
		glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	Shader ourShader("../src/vertex.shader", "../src/fragment.shader");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[72 * n];
	// float *vertices = (float *)malloc(18 * 4 * n * sizeof(float));
	float theta = 2 * 3.14159 / (float)n;
	int i = 0;
	float angle = 0;
	// ------------------------ all the rectangular faced
	// triangle-----------------

	for (int j = 0; j < n; j++) {
		float r = (float)rand() / (float)RAND_MAX;
		float g = (float)rand() / (float)RAND_MAX;
		float b = (float)rand() / (float)RAND_MAX;

		// 1st coordinate of triangle 1
		vertices[i++] = cos(angle);
		vertices[i++] = sin(angle);
		vertices[i++] = 0.5f;
		vertices[i++] = r;
		vertices[i++] = g;
		vertices[i++] = b;

		// 2nd coordinate of triangle 1
		vertices[i++] = cos(angle);
		vertices[i++] = sin(angle);
		vertices[i++] = -0.5f;
		vertices[i++] = r;
		vertices[i++] = g;
		vertices[i++] = b;

		// 3nd coordinate of triangle 1
		vertices[i++] = cos(angle + theta);
		vertices[i++] = sin(angle + theta);
		vertices[i++] = -0.5f;
		vertices[i++] = r;
		vertices[i++] = g;
		vertices[i++] = b;

		// 1st coordinate of triangle 2
		vertices[i++] = cos(angle);
		vertices[i++] = sin(angle);
		vertices[i++] = 0.5f;
		vertices[i++] = r;
		vertices[i++] = g;
		vertices[i++] = b;

		// 2nd coordinate of triangle 2
		vertices[i++] = cos(angle + theta);
		vertices[i++] = sin(angle + theta);
		vertices[i++] = 0.5f;
		vertices[i++] = r;
		vertices[i++] = g;
		vertices[i++] = b;

		// 3nd coordinate of triangle 2
		vertices[i++] = cos(angle + theta);
		vertices[i++] = sin(angle + theta);
		vertices[i++] = -0.5f;
		vertices[i++] = r;
		vertices[i++] = g;
		vertices[i++] = b;

		angle += theta;
	}
	// ------------------------------------------------ next is the top and
	// bottom triangle------------------------

	float r = (float)rand() / (float)RAND_MAX;
	float g = (float)rand() / (float)RAND_MAX;
	float b = (float)rand() / (float)RAND_MAX;
	angle = 0;
	for (int j = 0; j < n; j++) {
		// 1st coordinate of triangle 2
		vertices[i++] = cos(angle);
		vertices[i++] = sin(angle);
		vertices[i++] = 0.5f;
		vertices[i++] = r;
		vertices[i++] = g;
		vertices[i++] = b;

		// 2nd coordinate of triangle 2
		vertices[i++] = cos(angle + theta);
		vertices[i++] = sin(angle + theta);

		vertices[i++] = 0.5f;
		vertices[i++] = r;
		vertices[i++] = g;
		vertices[i++] = b;

		// 3nd coordinate of triangle 2
		vertices[i++] = 0.0f;
		vertices[i++] = 0.0f;
		vertices[i++] = 0.5f;
		vertices[i++] = r;
		vertices[i++] = g;
		vertices[i++] = b;
		angle += theta;
	}

	r = (float)rand() / (float)RAND_MAX;
	g = (float)rand() / (float)RAND_MAX;
	b = (float)rand() / (float)RAND_MAX;
	angle = 0;
	for (int j = 0; j < n; j++) {
		// 1st coordinate of triangle 2
		vertices[i++] = cos(angle);
		vertices[i++] = sin(angle);
		vertices[i++] = -0.5f;
		vertices[i++] = r;
		vertices[i++] = g;
		vertices[i++] = b;

		// 2nd coordinate of triangle 2
		vertices[i++] = cos(angle + theta);
		vertices[i++] = sin(angle + theta);
		vertices[i++] = -0.5f;
		vertices[i++] = r;
		vertices[i++] = g;
		vertices[i++] = b;

		// 3nd coordinate of triangle 2
		vertices[i++] = 0.0f;
		vertices[i++] = 0.0f;
		vertices[i++] = -0.5f;
		vertices[i++] = r;
		vertices[i++] = g;
		vertices[i++] = b;
		angle += theta;
	}

	unsigned int NUM_VERTICES = (sizeof(vertices) / sizeof(vertices[0])) / 6;

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s),
	// and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
						  (void *)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
						  (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered
	// VBO as the vertex attribute's bound vertex buffer object so afterwards we
	// can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally
	// modify this VAO, but this rarely happens. Modifying other VAOs requires a
	// call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
	// VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// enable depth testing for 3d
	glEnable(GL_DEPTH_TEST);
	glm::mat4 transform = glm::mat4(1.0f);
	while (!glfwWindowShouldClose(window)) {
		// print stuff for better understanding
		/*
		printf("\n");
		printf("Camera Position: %0.3f %0.3f %0.3f\n", camera.Position.x,
			   camera.Position.y, camera.Position.z);
		*/

		// input
		processInput(window);
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// make transformations
		// identity matrix
		glfwSetKeyCallback(window, key_callback);
		if (show) {
			transform = glm::rotate(transform, 0.02f,
									glm::vec3(0.0f, 0.01f, 0.0f));
		}
		if (t) {
			camera.Position = glm::vec3(10*sin(glfwGetTime()),10*cos(glfwGetTime()),0.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
			transform = glm::translate(transform,
									glm::vec3(0.0f, 0.1f, 0.0f));
		}
				if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
			transform = glm::translate(transform,
									glm::vec3(0.0f, -0.1f, 0.0f));
		}
				if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
			transform = glm::translate(transform,
									glm::vec3(0.1f, 0.00f, 0.0f));
		}
				if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
			transform = glm::translate(transform,
									glm::vec3(-0.1f, 0.0f, 0.0f));
		}
						if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
			transform = glm::translate(transform,
									glm::vec3(0.0f, 0.00f, 0.1f));
		}
				if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS){
			transform = glm::translate(transform,
									glm::vec3(0.0f, 0.0f, -0.1f));
		}
		
		ourShader.use();
		ourShader.setMat4("transform", transform);

		// view matrix
		glm::mat4 view = camera.GetViewMatrix(glm::vec3(0.0f));
		ourShader.setMat4("view", view);

		// projection matrix
		glm::mat4 projection = glm::perspective(
			glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
			0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		glBindVertexArray(VAO);  // seeing as we only have a single VAO there's
		// no need to bind it every time, but we'll do
		// so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
		// glBindVertexArray(0); // no need to unbind it every time

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse
		// moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;

}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = static_cast<float>(5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		glm::mat4(1.0f);
		camera.Position += cameraSpeed * camera.Front;}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.Position -= cameraSpeed * camera.Front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.Position -=
			glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.Position +=
			glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.Position += cameraSpeed * camera.Up;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.Position -= cameraSpeed * camera.Up;
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		camera.Position = (glm::vec3(-2.0f, -2.0f, 10.0f));
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		camera.Position = (glm::vec3(-20.0f, -20.0f, 10.0f));
	// if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	//   transform=glm::rotate(transform,(float)glfwGetTime(),glm::vec3(1,1,0));
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width
	// and height will be significantly larger than specified on retina
	// displays.
	glViewport(0, 0, width, height);
}
