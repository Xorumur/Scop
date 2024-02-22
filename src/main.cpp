#include <iostream>
#include "include/lib.h"
#include "vendors/glm/glm.hpp"
#include "vendors/glm/gtc/matrix_transform.hpp"
#include "vendors/glm/gtc/type_ptr.hpp"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include "Model/Model.hpp"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
string loadShaderSrc(const char *filename); 
void printMat4(const glm::mat4& matrix);

Mat4	finalMatrix = Mat4();

Mat4	rotationMatrix = Mat4();
Mat4	scaleMatrix = Mat4();
Mat4	translationMatrix = Mat4();

Mat4	createFinalMatrix()
{
	finalMatrix = Mat4();
	finalMatrix = finalMatrix * rotationMatrix;
	finalMatrix = finalMatrix * scaleMatrix;
	finalMatrix = finalMatrix * translationMatrix;
	return finalMatrix;
}

float zoomFactor = 0.2f;

// Keep track of the current rotation angle and the direction of rotation
float rotationAngle = 0.f;
float rotationDirectionX = 1.f;
float rotationDirectionY = 1.f;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
			// Make WASD rotate the model
			case GLFW_KEY_W:
				rotationMatrix = rotationMatrix.rotate(10.f, 1.f, 0.f, 0.f);
				break;
			case GLFW_KEY_S:
				rotationMatrix = rotationMatrix.rotate(10.f, -1.f, 0.f, 0.f);
				break;
			case GLFW_KEY_A:
				rotationMatrix = rotationMatrix.rotate(10.f, 0.0f, 1.f, 0.f);
				break;
			case GLFW_KEY_D:
				rotationMatrix = rotationMatrix.rotate(10.f, 0.0f, -1.f, 0.f);
				break;
		}
	}
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	float zoomFactor = 0.1f;

	// Zoom in
	if (yoffset > 0)
		scaleMatrix.scale(Vec3(1.0f + zoomFactor, 1.0f + zoomFactor, 1.0f + zoomFactor));
	// Zoom out
	else
		scaleMatrix.scale(Vec3(1.0f - zoomFactor, 1.0f - zoomFactor, 1.0f - zoomFactor));
}

int main(int ac, char **av)
{
	if (av[1] == NULL)
	{
		cout << "No object file specified" << endl;
		return 1;
	}

	Model model(av[1]);

	cout << "Loading model..." << endl;
	model.loadModel();
	cout << "Model loaded" << endl;

    int success;
    char infolog[512];

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // For MACOS
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "Scope", NULL, NULL);

    if (window == NULL)
    {
        cout << "Could not create window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        glfwTerminate();
        return -1;
    }    

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
		
	glfwSetKeyCallback(window, keyCallback);
	glfwSetScrollCallback(window, scrollCallback);

    // shaders 

    // Compile shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    string vertShaderSrc = loadShaderSrc("src/assets/vertex_core.glsl");
    const GLchar* vertShader = vertShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &vertShader, NULL);
    glCompileShader(vertexShader);


    // Catch error
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        cout << "Error with vertex shader compilation : " << infolog << endl;
    }

    // Compile fragment shader
    unsigned int fragmentShaders[2];
    fragmentShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
    string fragShaderSrc = loadShaderSrc("src/assets/fragment_core.glsl");
    const GLchar* fragShader = fragShaderSrc.c_str();
    glShaderSource(fragmentShaders[0], 1, &fragShader, NULL);
    glCompileShader(fragmentShaders[0]);

    // Catch error
    glGetShaderiv(fragmentShaders[0], GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaders[0], 512, NULL, infolog);
        cout << "Error with fragment shader compilation : " << infolog << endl;
    }


    // unsigned int fragmentShaders[2];
    fragmentShaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
    fragShaderSrc = loadShaderSrc("src/assets/fragment_core2.glsl");
    fragShader = fragShaderSrc.c_str();
    glShaderSource(fragmentShaders[1], 1, &fragShader, NULL);
    glCompileShader(fragmentShaders[1]);

    // Catch error
    glGetShaderiv(fragmentShaders[1], GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaders[1], 512, NULL, infolog);
        cout << "Error with fragment shader compilation : " << infolog << endl;
    }


    // Linking shader
    unsigned int shaderPrograms[2];
    shaderPrograms[0] = glCreateProgram();
    glAttachShader(shaderPrograms[0], vertexShader);
    glAttachShader(shaderPrograms[0], fragmentShaders[0]);
    glLinkProgram(shaderPrograms[0]);

    // Catch error
    glGetProgramiv(shaderPrograms[0], GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderPrograms[0], 512, NULL, infolog);
        cout << "Error during linking shader : " << infolog << endl; 
    }

    shaderPrograms[1] = glCreateProgram();
    glAttachShader(shaderPrograms[1], vertexShader);
    glAttachShader(shaderPrograms[1], fragmentShaders[1]);
    glLinkProgram(shaderPrograms[1]);

    // Catch error
    glGetProgramiv(shaderPrograms[1], GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderPrograms[1], 512, NULL, infolog);
        cout << "Error during linking shader : " << infolog << endl; 
    }   

    // Delete shader after linking them because we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaders[0]);
    glDeleteShader(fragmentShaders[1]);


	float* vertices2 = model.transformVertices();
	int* faces = model.transformFaces(); 


    // VAO, VBO
    unsigned VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind VAO
    glBindVertexArray(VAO);

    // bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.vertices.size() * 3, vertices2, GL_STATIC_DRAW);

    // set attribute pointer

    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // set up EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * model.faces.size() * 3, faces, GL_STATIC_DRAW);

    // glm::mat4 trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.2));
	scaleMatrix.scale(Vec3(0.2, 0.2, 0.2));
    glUseProgram(shaderPrograms[0]);
    // glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
    while(!glfwWindowShouldClose(window))
    {
        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); 

        // trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // // glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		
		// scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.2));

		glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[0], "transform"), 1, GL_FALSE, createFinalMatrix().GetDataPtr());

        // draw shapes
        glBindVertexArray(VAO);

        // First triangle
        glUseProgram(shaderPrograms[0]);
        glDrawElements(GL_TRIANGLES, model.faces.size() * 3, GL_UNSIGNED_INT, 0);

        // second triangle
        // glUseProgram(shaderPrograms[1]);
        // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));
        // Send new frame to window
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

string loadShaderSrc(const char *filename) {
    ifstream file;
    stringstream buf;

    string ret("");

    file.open(filename);

    if (file.is_open()) {
        buf << file.rdbuf();
        ret = buf.str();
    }
    else {
        cout << "Could not open " << filename << endl;
    }

    file.close();

    return ret;
}

void printMat4(const glm::mat4& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
