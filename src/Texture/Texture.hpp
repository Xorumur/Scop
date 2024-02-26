#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Texture
{
	public:

	string					filePath;
	string					textureName;

	// float					ambient[3]; // Ka: Ambient color
	// float					diffuse[3]; // Kd: Diffuse color
	// float					specular[3]; // Ks: Specular color

	// float					Ns; // Ns: Specular exponent
	// float 					Ni; // Ni: Optical density

	// float					d; // d: Dissolve factor (transparency)
	// float					illum; // illum: Illumination model

	Texture();
	Texture(string path);
	~Texture();

	bool					loadTexture();

	// print operator overload
	friend ostream& operator<<(ostream& os, const Texture& texture);
};

#endif