#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "../vendors/stb/stb_image.h"
#include "../include/lib.h"


using namespace std;

class Texture
{

    public:
        int width, height, nrChannels;
        unsigned char *data;
        unsigned int textureID;

        Texture();
        Texture(string path);
        ~Texture();

	bool					loadTexture();

	// print operator overload
	friend ostream& operator<<(ostream& os, const Texture& texture);
};

#endif