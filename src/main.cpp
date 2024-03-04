#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include "lib.h"

#include "Model/Model.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "Shader/Shader.hpp"
//#include "Texture/Texture.hpp"

using namespace std;

Model	model;
Shader shader;

void	framebufferSizeCallback(GLFWwindow* window, int width, int height);
void	keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void	scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void	dropCallback(GLFWwindow* window, int count, const char* paths[]);

GLFWwindow *initWindow() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// For MACOS
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	GLFWwindow* window = glfwCreateWindow(800, 600, "Scop", NULL, NULL);

	if (window == NULL)
	{
		cout << "Could not create window" << endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		glfwTerminate();
		return NULL;
	}


	glViewport(0, 0, 1600, 1200);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  
	glfwSetKeyCallback(window, keyCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetDropCallback(window, dropCallback);
	return window;
}

int main(int ac, char **av)
{
	if (av[1] == NULL)
	{
		cout << "No object file specified" << endl;
		return 1;
	}

	GLFWwindow *window = initWindow();
	if (!window) return 1;

	model = Model(av[1]);
	model.loadModel();

	if (model.vertices.size() == 0 || model.faces.size() == 0)
	{
		cout << "Exiting: Model invalid." << endl;
		return 1;
	}

    shader = Shader("./src/Shader/shaders/vertex_core.glsl", "./src/Shader/shaders/fragment_core.glsl");

	model.texLoc =  glGetUniformLocation(shader.id, "tex");

	shader.activate();

    model.setVertices(NO_COLOR_MODE);

	cout << model << endl;

	while (!glfwWindowShouldClose(window))
	{
		// rendering
		glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model.Rotate(0.2f, 0.0f, 1.f, 0.0f);

		glUniformMatrix4fv(glGetUniformLocation(shader.id, "transform"), 1, GL_FALSE, model.createFinalMatrix().GetDataPtr());
		
		glDrawElements(GL_TRIANGLES, model.faces.size() * 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();    
	}

	model.deleteBuffers();

	glfwTerminate();

	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		// cout << "Key: " << key << endl;
		switch (key) {
			// Make WASD rotate the model
			case GLFW_KEY_W:
				model.Rotate(10.f, 1.f, 0.f, 0.f);
				break;
			case GLFW_KEY_S:
				model.Rotate(10.f, -1.f, 0.f, 0.f);
				break;
			case GLFW_KEY_A:
				model.Rotate(10.f, 0.f, 1.f, 0.f);
				break;
			case GLFW_KEY_D:
				model.Rotate(10.f, 0.f, -1.f, 0.f);
				break;
			case GLFW_KEY_E: // GLFW_KEY_1
				// default mode
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				break;
			case GLFW_KEY_R: // GLFW_KEY_2
				// only edges mode
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				break;
			case GLFW_KEY_T: // GLFW_KEY_3
				// only vertices mode
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				break;
			case GLFW_KEY_LEFT: // GLFW_KEY_4
				model.setVertices(NO_COLOR_MODE);
				break;
			case GLFW_KEY_RIGHT: // GLFW_KEY_5
				model.setVertices(RAND_COLOR_MODE);
				break;
			case GLFW_KEY_UP: // GLFW_KEY_6
				model.setVertices(TEXTURE_MODE);
				break;
		}
	}
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	// Zoom in
	if (yoffset > 0)
		model.Scale(1.1f);

	// Zoom out
	else
		model.Scale(0.9f);
}

void	dropCallback(GLFWwindow* window, int count, const char* paths[]) {
	for (int i = 0; i < count; i++) {
		const char* path = paths[i];
		
		cout << "Dropped file: " << path << endl;

		if (model.texture.loadTexture(path))
			model.setVertices(TEXTURE_MODE);
	}
}