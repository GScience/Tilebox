#include "Application.h"
using namespace std;

int main(int argc, char* argv[])
{
	LaunchArgs args;

	for (auto i = 1u; i < argc; ++i)
		args.push_back(argv[i]);

	Application app;
	app.Launch(args);
}