#include "Material.hpp"

Material::Material() {
	this->materialName = "";

	this->ambient[0] = 0.0f; this->ambient[1] = 0.0f; this->ambient[2] = 0.0f;
	this->diffuse[0] = 0.0f; this->diffuse[1] = 0.0f; this->diffuse[2] = 0.0f;
	this->specular[0] = 0.0f; this->specular[1] = 0.0f; this->specular[2] = 0.0f;

	this->Ns = 0.0f;
	this->Ni = 0.0f;

	this->d = 0.0f;
	this->illum = 0.0f;
}

Material::Material(string filePath) : Material() {
	this->filePath = filePath;
}

Material::~Material() { }

void Material::loadMaterial() {
	ifstream	file(this->filePath);
	string		line;

	if (!file.is_open()) {
		cout << "loadMaterial: unable to open file: " << this->filePath << endl;
		return ;
	}
	while (getline(file, line))
		this->parseLine(line);
	file.close();
}

void Material::parseLine(string line) {
	if (line[0] == 'n' && line[1] == 'e' && line[2] == 'w' && line[3] == 'm' && line[4] == 't' && line[5] == 'l') {
		this->parseMaterialName(line);
	}
	else if (line[0] == 'K' && line[1] == 'a') {
		this->parseAmbient(line);
	}
	else if (line[0] == 'K' && line[1] == 'd') {
		this->parseDiffuse(line);
	}
	else if (line[0] == 'K' && line[1] == 's') {
		this->parseSpecular(line);
	}
	else if (line[0] == 'N' && line[1] == 's') {
		this->parseSpecularExponent(line);
	}
	else if (line[0] == 'N' && line[1] == 'i') {
		this->parseOpticalDensity(line);
	}
	else if (line[0] == 'd' && line[1] == ' ') {
		this->parseDissolve(line);
	}
	else if (line[0] == 'i' && line[1] == 'l' && line[2] == 'l' && line[3] == 'u' && line[4] == 'm') {
		this->parseIlluminationModel(line);
	}
}

void Material::parseMaterialName(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->materialName;
}

void Material::parseAmbient(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->ambient[0];
	ss >> this->ambient[1];
	ss >> this->ambient[2];
}

void Material::parseDiffuse(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->diffuse[0];
	ss >> this->diffuse[1];
	ss >> this->diffuse[2];
}

void Material::parseSpecular(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->specular[0];
	ss >> this->specular[1];
	ss >> this->specular[2];
}

void Material::parseSpecularExponent(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->Ns;
}

void Material::parseOpticalDensity(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->Ni;
}

void Material::parseDissolve(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->d;
}

void Material::parseIlluminationModel(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->illum;
}

ostream& operator<<(ostream& os, const Material& material) {
	os << "Material: '" << material.materialName << "'" << endl;
	os << "  Ambient: " << material.ambient[0] << " | " << material.ambient[1] << " | " << material.ambient[2] << endl;
	os << "  Diffuse: " << material.diffuse[0] << " | " << material.diffuse[1] << " | " << material.diffuse[2] << endl;
	os << "  Specular: " << material.specular[0] << " | " << material.specular[1] << " | " << material.specular[2] << endl;
	os << "  Specular exponent: " << material.Ns << endl;
	os << "  Optical density: " << material.Ni << endl;
	os << "  Dissolve factor: " << material.d << endl;
	os << "  Illumination model: " << material.illum;
	return os;
}

