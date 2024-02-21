#include "Scop.hpp"
#include "Model/Model.hpp"

using namespace std;

int	mainGLFW(Model& model);

int main(int ac, char **av)
{
	if (av[1] == NULL)
	{
		cout << "No object file specified" << endl;
		return 1;
	}

	Model model(av[1]);

	cout << "Loading model..." << endl;
	model.loadModel();
	cout << "Model loaded" << endl;

	// cout << model;

	mainGLFW(model);

	return 0;
}