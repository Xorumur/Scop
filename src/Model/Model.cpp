#include "Model.hpp"
#include "../include/lib.h"

using namespace std;

Model::Model() { }

Model::Model(string filePath)
{
	this->filePath = filePath;
}

Model::~Model() { }

void Model::loadModel()
{
	ifstream	file(this->filePath);
	string		line;

	if (!file.is_open()) {
		cout << "loadModel: Unable to open file: " << this->filePath << endl;
		return ;
	}
	while (getline(file, line))
		this->parseLine(line);
	file.close();
}

void Model::parseLine(string line)
{
	if (line[0] == 'v' && line[1] == ' ') {
		this->parseVertex(line);
	}
	else if (line[0] == 'f' && line[1] == ' ') {
		this->parseFace(line);
	}
	else if (line[0] == 'm' && line[1] == 't' && line[2] == 'l' && line[3] == 'l' && line[4] == 'i' && line[5] == 'b') {
		this->parseTextureLib(line);
	}
	else if (line[0] == 'u' && line[1] == 's' && line[2] == 'e' && line[3] == 'm' && line[4] == 't' && line[5] == 'l') {
		this->parseTexture(line);
	}
	else if (line[0] == 's' && line[1] == ' ') {
		this->parseSmoothing(line);
	}
	else if (line[0] == 'o' && line[1] == ' ') {
		this->parseObjectName(line);
	}
}

void Model::parseVertex(string line)
{
	vector<float> vertex;
	stringstream ss(line);
	string word;
	float value;

	ss >> word;
	while (ss >> value) {
		vertex.push_back(value);
	}
	this->vertices.push_back(vertex);
}

void Model::parseFace(string line)
{
	vector<int> face;
	stringstream ss(line);
	string word;
	int value;

	ss >> word;
	while (ss >> value) {
		face.push_back(value);
	}

	// Triangulate the face if it has 4 vertices
	if (face.size() == 4) {
		vector<int> newFace1 = { face[0], face[1], face[2] };
		vector<int> newFace2 = { face[2], face[3], face[0] };
		this->faces.push_back(newFace1);
		this->faces.push_back(newFace2);
	}
	else
		this->faces.push_back(face);
}

void Model::parseTextureLib(string line)
{
	stringstream ss(line);
	string word;
	string value;

	ss >> word;
	ss >> value;
	this->textureLib = value;
	// The texture file path is the same as the object file path but with the .mtl extension
	this->texture.filePath = this->filePath.substr(0, this->filePath.find_last_of('.')) + ".mtl";

	cout << "Texture file path: " << this->texture.filePath << endl;

	cout << "Loading texture..." << endl;
	this->textureAvailable = this->texture.loadTexture();

	if (this->textureAvailable == false)
		cout << "Texture not found / unavailable" << endl;
	else
		cout << "Texture loaded: " << this->texture << endl;

}

void Model::parseTexture(string line)
{
	stringstream ss(line);
	string word;
	string value;

	ss >> word;
	ss >> value;
	this->texture.textureName = value;
}

void Model::parseSmoothing(string line)
{
	stringstream ss(line);
	string word;
	string value;

	ss >> word;
	ss >> value;
	this->smoothing = value;
}

void Model::parseObjectName(string line)
{
	stringstream ss(line);
	string word;
	string value;

	ss >> word;
	ss >> value;
	this->modelName = value;
}

// Rotate the model by specified angles around the X, Y, and Z axes.
void Model::Rotate(float angle, float dirX, float dirY, float dirZ)
{
	this->rotationMatrix = this->rotationMatrix.rotate(angle, dirX, dirY, dirZ);
}

// Translate (move) the model by specified offsets in the X, Y, and Z directions.
void Model::Translate(float offsetX, float offsetY, float offsetZ)
{
	this->translationMatrix.translate(Vec3(offsetX, offsetY, offsetZ));
}

// Scale the model uniformly by a specified factor.
void Model::Scale(float scale)
{
	this->scaleMatrix.scale(Vec3(scale, scale, scale));
}

Mat4 Model::createFinalMatrix()
{
	// Create final transformation matrix
	Mat4 finalMatrix = Mat4();
	finalMatrix = finalMatrix * rotationMatrix;
	finalMatrix = finalMatrix * scaleMatrix;
	finalMatrix = finalMatrix * translationMatrix;
	return finalMatrix;
}

float*					Model::transformVertices() {
	float* vertices = new float[this->vertices.size() * currMode];
	int i = 0;
	for (auto& vertex : this->vertices) {
		vertices[i] = vertex[0];
		vertices[i + 1] = vertex[1];
		vertices[i + 2] = vertex[2];
		if (vertex.size() == 6 ) {
			vertices[i + 3] = vertex[3];
			vertices[i + 4] = vertex[4];
			vertices[i + 5] = vertex[5];
			i += 6;
		}
		else {
			i += 3;
		}
	}
	return vertices;
}

int*					Model::transformFaces() {
	int* faces = new int[this->faces.size() * 3];
	int i = 0;
	for (auto& face : this->faces) {
		faces[i] = face[0] - 1;
		faces[i + 1] = face[1] - 1;
		faces[i + 2] = face[2] - 1;
		i += 3;
	}
	return faces;
}

void printVertices(vector<vector<float>> vertices) {
	for (auto& vertex : vertices) {
		cout << "Vertex: ";
		for (auto& value : vertex) {
			cout << value << " ";
		}
		cout << endl;
	}
}

float randomFloat() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Model::setVertices(int mode)
{
	vector<vector<float>> newVertices;

	if (mode == 0) {
		for (int i = 0; i < this->vertices.size(); i++) {
			vector<float> vertex = this->vertices[i];
			vertex.push_back(1.0f);
			vertex.push_back(1.0f);
			newVertices.push_back(vertex);
		}
		printVertices(newVertices);
	}
	else if (mode == COLOR_MODE) {
		for (int i = 0; i < this->vertices.size(); i++) {
			vector<float> vertex = this->vertices[i];
			// Replace / Insert the color values at the end of the vertex / at the 3rd index
			if (vertex.size() == 3) {
				vertex.push_back(randomFloat());
				vertex.push_back(randomFloat());
				vertex.push_back(randomFloat());
			}
			else {
				vertex[3] = randomFloat();
				vertex[4] = randomFloat();
				vertex[5] = randomFloat();
			}
			newVertices.push_back(vertex);
		}
		this->currMode = COLOR_MODE;
		this->vertices = newVertices;
		setupBuffers();
	}

	// this->vertices = this->vertices;
}

void Model::loadTexture() {
	this->texture.loadTexture();
}

void Model::setupBuffers() {
	float* vertices = this->transformVertices();
	int* faces = this->transformFaces(); 

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind VAO
	glBindVertexArray(VAO);

	// bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertices.size() * currMode, vertices, GL_STATIC_DRAW);

	// set attribute pointer

	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, currMode * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// colors
	if (currMode == COLOR_MODE) {
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, currMode * sizeof(float), (void*)(3 * sizeof(float))); // Décalage de 3 composantes
		glEnableVertexAttribArray(1);
	}

	// set up EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * this->faces.size() * 3, faces, GL_STATIC_DRAW);
}

void Model::deleteBuffers() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


ostream& operator<<(ostream& os, const Model& model)
{
	os << "Model: " << model.modelName << endl;
	os << "  Smoothing: " << model.smoothing << endl;
	os << "  Vertices: " << model.vertices.size() << endl;
	os << "  Faces: " << model.faces.size() << endl;
	os << "  Texture Library: " << model.textureLib << endl;
	os << model.texture << endl;
	return os;
}