#include <iostream>
#include "vendors/GLFW/glfw3.h"
#include "Model/Model.hpp"
#include "Material/Material.hpp"
#include "Scop.hpp"

#define GL_SILENCE_DEPRECATION true

using namespace std;

float camX = 0.f, camY = 0.f, camZ = 0.f;
float rotationX = 0.0f;
float rotationY = 0.0f;
float scale = 0.2f;

void errorCallbak(int error, const char* description)
{
	fputs(description, stderr);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "Key: '" << key << "' | Action: '" << action << "'" << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_LEFT:
                camX -= 0.02f;
                break;
            case GLFW_KEY_RIGHT:
                camX += 0.02f;
                break;
            case GLFW_KEY_UP:
                camY += 0.02f;
                break;
            case GLFW_KEY_DOWN:
                camY -= 0.02f;
                break;
			// Make WASD rotate the model
			case GLFW_KEY_W:
                rotationX += 10.f;
				break;
			case GLFW_KEY_S:
                rotationX -= 10.f;
				break;
			case GLFW_KEY_A:
                rotationY += 10.f;
				break;
			case GLFW_KEY_D:
                rotationY -= 10.f;
				break;
			case GLFW_KEY_Z:
				scale += 0.1f;
				break;
			case GLFW_KEY_X:
				scale -= 0.1f;
				break;
		}
    }
}

// float triangleVertices[] = {
//     -0.6f, -0.4f, -1.0f,
//      0.6f, -0.4f, -1.0f,
//      0.0f,  0.6f,  1.0f
// };

// float quadVertices[12][9] = {
// 	// South face
// 	{ 0, 0, 0,    0, 1, 0,    1, 1, 0, },
// 	{ 0, 0, 0,    1, 1, 0,    1, 0, 0, },

// 	// East face
// 	{ 1, 0, 0,    1, 1, 0,    1, 1, 1, },
// 	{ 1, 0, 0,    1, 1, 1,    1, 0, 1, },

// 	// North face
// 	{ 1, 0, 1,    1, 1, 1,    0, 1, 1, },
// 	{ 1, 0, 1,    0, 1, 1,    0, 0, 1, },

// 	// West face
// 	{ 0, 0, 1,    0, 1, 1,    0, 1, 0, },
// 	{ 0, 0, 1,    0, 1, 0,    0, 0, 0, },

// 	// Top face
// 	{ 0, 1, 0,    0, 1, 1,    1, 1, 1, },
// 	{ 0, 1, 0,    1, 1, 1,    1, 1, 0, },

// 	// Bottom face
// 	{ 1, 0, 1,    0, 0, 1,    0, 0, 0, },
// 	{ 1, 0, 1,    0, 0, 0,    1, 0, 0, },
// };

// // Colors for 6 faces
// float quadColors[6][3] = {
// 	{ 1, 0, 0 },
// 	{ 0, 1, 0 },
// 	{ 0, 0, 1 },
// 	{ 1, 1, 0 },
// 	{ 1, 0, 1 },
// 	{ 0, 1, 1 },
// };

// void drawQuad() {
// 	int i = 0;
// 	float color[3];
// 	for (auto& vertex : quadVertices) {
// 		glBegin(GL_TRIANGLES);
// 		glColor3fv(&quadColors[i / 2][0]);
// 		glVertex3fv(&vertex[0]);
// 		glVertex3fv(&vertex[3]);
// 		glVertex3fv(&vertex[6]);
// 		glEnd();
// 		i++;
// 	}
// }

GLFWwindow* initWindow()
{
	GLFWwindow* window;

	glfwSetErrorCallback(errorCallbak);

	/* Initialize the library */
	if (!glfwInit())
		return NULL;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(720, 720, "Scop", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return NULL;
	}

	glfwSetKeyCallback(window, keyCallback);
	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	return window;
}

void	gameLoop(GLFWwindow* window, Model& model)
{
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float) height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		// Translate = Move the model
        glTranslatef(camX, camY, camZ);

		// Scale = Zoom in/out
		glScalef(scale, scale, scale);

		// Rotate the model with X and Y
		glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

		model.drawModel();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

int mainGLFW(Model& model)
{
	GLFWwindow* window = initWindow();
	if (!window) return 1;

	gameLoop(window, model);

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}