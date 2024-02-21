#ifndef MODEL_HPP
# define MODEL_HPP

#include "../Material/Material.hpp"

// A shaderProgram consists of at least two types of shaders:
// 	-	Vertex Shader (vertexShader): Processes each vertex of a 3D model, transforming its position and passing data to the next stages of the pipeline.
// 	-	Fragment Shader (fragmentShader): Processes fragments (pixels) generated by rasterizing the 3D model. It determines the final color of each pixel.

using namespace std;

class Model
{
	public:

	string					filePath; // Path to the .obj file

	string					modelName; // o: Indicates the start of a new object in the .obj file

	string					materialLib; // mtllib: Specifies the material library file.
	Material				material; // usemtl: Specifies the material used for the faces following it.
	string					smoothing; // s: Smoothing on or off (on is the default)

	vector<vector<float> >	vertices; // v: Geometric vertices
	vector<vector<int> >	faces; // f: Face elements

	Model(string filePath);
	~Model();

	void					loadModel();
	void					parseLine(string line);

	void					parseVertex(string line);
	void					parseFace(string line);
	void					parseMaterialLib(string line);
	void					parseMaterial(string line);
	void					parseSmoothing(string line);
	void					parseObjectName(string line);

	// Rotate the model by specified angles around the X, Y, and Z axes.
	void	Rotate(float angleX, float angleY, float angleZ);

	// Translate (move) the model by specified offsets in the X, Y, and Z directions.
	void	Translate(float offsetX, float offsetY, float offsetZ);

	// Scale the model uniformly by a specified factor.
	void	Scale(float scale);

	// void	drawModel();

	// print operator overload
	friend ostream& operator<<(ostream& os, const Model& model);
};

#endif