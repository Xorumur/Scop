#include "Shader.hpp"

Shader::Shader(const char * vertexShaderPath, const char * fragmentShaderPath) {
	GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	int success;
	char infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint Shader::compileShader(const char* filepath, GLenum type) {
	GLuint shader = glCreateShader(type);
	string shaderString = loadShaderString(filepath);
	const char* shaderSource = shaderString.c_str();
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" << infoLog << endl;
	}

	return shader;
}

void Shader::activate() {
	glUseProgram(this->id);
}

string Shader::loadShaderString(const char *filename) {
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
};