
#pragma once

#include <iomanip>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string> 

#include "../vendors/glad/glad.h"
#include "../vendors/GLFW/glfw3.h"
#include "../Scop.hpp"

class Shader {
    public:
        unsigned int id;

        Shader(const char * vertexShaderPath, const char * fragmentShaderPath);
        void activate();

        string loadShaderString(const char* filepath);
        GLuint compileShader(const char* filepath, GLenum type);

        // uniform functions
        void setMat4(std::string name, Mat4 val);
};
