#include "Scop.hpp"
#include "Model/Model.hpp"
#include "Material/Material.hpp"

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

	model.loadModel();

	cout << model;

	mainGLFW(model);

	return 0;
}