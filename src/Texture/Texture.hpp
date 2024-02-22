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
	string					textureName; // newmtl: Declares the name of a texture

	float					ambient[3]; // Ka: Ambient color
	float					diffuse[3]; // Kd: Diffuse color
	float					specular[3]; // Ks: Specular color

	float					Ns; // Ns: Specular exponent
	float 					Ni; // Ni: Optical density

	float					d; // d: Dissolve factor (transparency)
	float					illum; // illum: Illumination model

	Texture();
	Texture(string path);
	~Texture();

	bool					loadTexture();
	void					parseLine(string line);
	void					parseTextureName(string line);
	void					parseAmbient(string line);
	void					parseDiffuse(string line);
	void					parseSpecular(string line);
	void					parseSpecularExponent(string line);
	void					parseOpticalDensity(string line);
	void					parseDissolve(string line);
	void					parseIlluminationModel(string line);

	// print operator overload
	friend ostream& operator<<(ostream& os, const Texture& texture);
};

#endif