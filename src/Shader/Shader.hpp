#ifndef SHADER_H
    #define SHADER_H

#include "../vendors/glad/glad.h"
#include "../vendors/GLFW/glfw3.h"
// #include "../vendors/glm/glm.hpp"
// #include "../vendors/glm/gtc/matrix_transform.hpp"
// #include "../vendors/glm/gtc/type_ptr.hpp"
#include "math.hpp"
#include "../Scop.hpp"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string> 

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

#endif