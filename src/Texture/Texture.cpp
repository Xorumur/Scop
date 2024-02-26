#include "Texture.hpp"

Texture::Texture() {

}

Texture::Texture(string filePath) : Texture() {
	this->filePath = filePath;
}

Texture::~Texture() { }

bool	Texture::loadTexture() {
	// ifstream	file(this->filePath);
	// string		line;

	// if (!file.is_open()) {
	// 	cout << "loadTexture: unable to open file: " << this->filePath << endl;
	// 	return false;
	// }
	// while (getline(file, line))
	// 	this->parseLine(line);
	// file.close();
	// return true;
}

ostream& operator<<(ostream& os, const Texture& texture) {
	// os << "Texture: '" << texture.textureName << "'" << endl;
	// os << "  Ambient: " << texture.ambient[0] << " | " << texture.ambient[1] << " | " << texture.ambient[2] << endl;
	// os << "  Diffuse: " << texture.diffuse[0] << " | " << texture.diffuse[1] << " | " << texture.diffuse[2] << endl;
	// os << "  Specular: " << texture.specular[0] << " | " << texture.specular[1] << " | " << texture.specular[2] << endl;
	// os << "  Specular exponent: " << texture.Ns << endl;
	// os << "  Optical density: " << texture.Ni << endl;
	// os << "  Dissolve factor: " << texture.d << endl;
	// os << "  Illumination model: " << texture.illum;
	return os;
}

