#include "Texture.hpp"

Texture::Texture() {
	this->textureName = "";

	this->ambient[0] = 0.0f; this->ambient[1] = 0.0f; this->ambient[2] = 0.0f;
	this->diffuse[0] = 0.0f; this->diffuse[1] = 0.0f; this->diffuse[2] = 0.0f;
	this->specular[0] = 0.0f; this->specular[1] = 0.0f; this->specular[2] = 0.0f;

	this->Ns = 0.0f;
	this->Ni = 0.0f;

	this->d = 0.0f;
	this->illum = 0.0f;
}

Texture::Texture(string filePath) : Texture() {
	this->filePath = filePath;
}

Texture::~Texture() { }

bool	Texture::loadTexture() {
	ifstream	file(this->filePath);
	string		line;

	if (!file.is_open()) {
		cout << "loadTexture: unable to open file: " << this->filePath << endl;
		return false;
	}
	while (getline(file, line))
		this->parseLine(line);
	file.close();
	return true;
}

void Texture::parseLine(string line) {
	if (line[0] == 'n' && line[1] == 'e' && line[2] == 'w' && line[3] == 'm' && line[4] == 't' && line[5] == 'l') {
		this->parseTextureName(line);
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

void Texture::parseTextureName(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->textureName;
}

void Texture::parseAmbient(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->ambient[0];
	ss >> this->ambient[1];
	ss >> this->ambient[2];
}

void Texture::parseDiffuse(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->diffuse[0];
	ss >> this->diffuse[1];
	ss >> this->diffuse[2];
}

void Texture::parseSpecular(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->specular[0];
	ss >> this->specular[1];
	ss >> this->specular[2];
}

void Texture::parseSpecularExponent(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->Ns;
}

void Texture::parseOpticalDensity(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->Ni;
}

void Texture::parseDissolve(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->d;
}

void Texture::parseIlluminationModel(string line) {
	stringstream ss(line);
	string word;

	ss >> word;
	ss >> this->illum;
}

ostream& operator<<(ostream& os, const Texture& texture) {
	os << "Texture: '" << texture.textureName << "'" << endl;
	os << "  Ambient: " << texture.ambient[0] << " | " << texture.ambient[1] << " | " << texture.ambient[2] << endl;
	os << "  Diffuse: " << texture.diffuse[0] << " | " << texture.diffuse[1] << " | " << texture.diffuse[2] << endl;
	os << "  Specular: " << texture.specular[0] << " | " << texture.specular[1] << " | " << texture.specular[2] << endl;
	os << "  Specular exponent: " << texture.Ns << endl;
	os << "  Optical density: " << texture.Ni << endl;
	os << "  Dissolve factor: " << texture.d << endl;
	os << "  Illumination model: " << texture.illum;
	return os;
}

