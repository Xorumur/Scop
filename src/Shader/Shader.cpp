#include "Shader.hpp"

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