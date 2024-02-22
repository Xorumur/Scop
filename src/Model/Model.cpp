#include "Model.hpp"

using namespace std;

// Function to generate a random r g b color for the vertices
void randomColorTest(float* color) {
	for (int i = 0; i < 3; ++i) {
		color[i] = (rand() % 100) / 100.0f;
	}
}

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
		this->parseMaterialLib(line);
	}
	else if (line[0] == 'u' && line[1] == 's' && line[2] == 'e' && line[3] == 'm' && line[4] == 't' && line[5] == 'l') {
		this->parseMaterial(line);
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

void Model::parseMaterialLib(string line)
{
	stringstream ss(line);
	string word;
	string value;

	ss >> word;
	ss >> value;
	this->materialLib = value;
	this->material.filePath = "resources/" + value;
	this->material.loadMaterial();
}

void Model::parseMaterial(string line)
{
	stringstream ss(line);
	string word;
	string value;

	ss >> word;
	ss >> value;
	this->material.materialName = value;
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

void Model::Rotate(float angleX, float angleY, float angleZ)
{
	// Rotate the model by specified angles around the X, Y, and Z axes.
}

void Model::Translate(float offsetX, float offsetY, float offsetZ)
{
	// Translate (move) the model by specified offsets in the X, Y, and Z directions.
}

void Model::Scale(float scale)
{
	// Scale the model uniformly by a specified factor.
}

// void Model::drawModel()
// {


// 	// Set ambient color
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this->material.ambient);
// 	// Set diffuse color
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->material.diffuse);
// 	// Set specular color
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, this->material.specular);
// 	// Set shininess/exponent
// 	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->material.Ns);

// 	for (auto& face : this->faces) {
// 		glBegin(GL_TRIANGLES);
// 		for (auto& vertex : face) {
// 			float color[3];
// 			randomColorTest(color);
// 			glColor3fv(color);
// 			glVertex3fv(&this->vertices[vertex - 1][0]);
// 		}
// 		glEnd();
// 	}
// }

float*					Model::transformVertices() {
	float* vertices = new float[this->vertices.size() * 3];
	int i = 0;
	for (auto& vertex : this->vertices) {
		vertices[i] = vertex[0];
		vertices[i + 1] = vertex[1];
		vertices[i + 2] = vertex[2];
		i += 3;
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

ostream& operator<<(ostream& os, const Model& model)
{
	os << "Model: " << model.modelName << endl;
	os << "  Smoothing: " << model.smoothing << endl;
	os << "  Vertices: " << model.vertices.size() << endl;
	os << "  Faces: " << model.faces.size() << endl;
	os << "  Material Library: " << model.materialLib << endl;
	os << model.material << endl;
	return os;
}