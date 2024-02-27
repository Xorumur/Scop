#include "Texture.hpp"

Texture::Texture() {

}

Texture::Texture(string filePath) : Texture() {
	glGenTextures(1, &this->textureID);
    glBindTexture(GL_TEXTURE_2D, this->textureID);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    this->data = stbi_load("./resources/container.jpg", &this->width, &this->height, &this->nrChannels, 0);
    if (this->data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(this->data);
    cout << "Texture loaded" << endl;
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

