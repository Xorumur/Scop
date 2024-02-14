#pragma once

#include "../Scop.hpp"

using namespace std;

class Material
{
	public:

	string					filePath;
	string					materialName; // newmtl: Declares the name of a material

	float					ambient[3]; // Ka: Ambient color
	float					diffuse[3]; // Kd: Diffuse color
	float					specular[3]; // Ks: Specular color
	
	float					Ns; // Ns: Specular exponent
	float 					Ni; // Ni: Optical density

	float					d; // d: Dissolve factor (transparency)
	float					illum; // illum: Illumination model

	Material();
	Material(string path);
	~Material();

	void					loadMaterial();
	void					parseLine(string line);
	void					parseMaterialName(string line);
	void					parseAmbient(string line);
	void					parseDiffuse(string line);
	void					parseSpecular(string line);
	void					parseSpecularExponent(string line);
	void					parseOpticalDensity(string line);
	void					parseDissolve(string line);
	void					parseIlluminationModel(string line);

	// print operator overload
	friend ostream& operator<<(ostream& os, const Material& material);
};