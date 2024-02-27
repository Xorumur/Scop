#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "../vendors/stb/stb_image.h"
#include "../include/lib.h"
#include "../Shader/Shader.hpp"

using namespace std;

class Texture
{

    public:
        int                 width, height, nrChannels;
        unsigned char       *data;
        unsigned int        textureID;
        bool                active = false;

        Texture();
        Texture(string path);
        ~Texture();

    void                    bindShader(const Shader& shader);
	bool					loadTexture();
    void                    setActive(Shader shader);
    void                    unactive();

	// print operator overload
	friend ostream& operator<<(ostream& os, const Texture& texture);
};

#endif