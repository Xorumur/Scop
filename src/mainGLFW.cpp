#include "Scop.hpp"
#include "Model/Model.hpp"
#include "Shader/Shader.hpp"

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

GLFWwindow* initWindow()
{
	GLFWwindow*		window;

	glfwSetErrorCallback(errorCallbak);

	/* Initialize the library */
	if (!glfwInit())
		return NULL;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// For MACOS
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

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

void	gameLoop(GLFWwindow* window, Model& model, Shader& shaderProgram, unsigned int VAO)
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

		// trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		// glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(trans));

		// draw shapes
		glBindVertexArray(VAO);

		glUseProgram(shaderProgram.id);

		// Draw the model with all the data we set up
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// // Translate = Move the model
		// glTranslatef(camX, camY, camZ);

		// // Scale = Zoom in/out
		// glScalef(scale, scale, scale);

		// // Rotate the model with X and Y
		// glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
        // glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

		// // model.drawModel();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

void	initBuffersData(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, Model& model)
{

	cout << "glGenVertexArrays" << endl;
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer and faces buffer.
	glBindVertexArray(*VAO);

	// VBO is our array of vertices (Vextex Buffer Object), we bind it to our VAO
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.vertices[0]) * model.vertices.size(), &model.vertices[0], GL_STATIC_DRAW);

	// EBO is our array of faces (Element Buffer Object), we bind it to our VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.faces[0]) * model.faces.size(), &model.faces[0], GL_STATIC_DRAW);

	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// VAO will contain the layout of our VBO and EBO
}

int mainGLFW(Model& model)
{
	GLFWwindow* window = initWindow();
	if (!window) return 1;

	cout << "Loading shaders..." << endl;
	Shader shader = Shader("src/Shader/Programs/vertex.glsl", "src/Shader/Programs/fragment.glsl");
	cout << "Shaders loaded" << endl;

	cout << "Init buffers data..." << endl;
	unsigned int VAO, VBO, EBO;
	initBuffersData(&VAO, &VBO, &EBO, model);
	cout << "Buffers data initialized" << endl;

	gameLoop(window, model, shader, VAO);

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}