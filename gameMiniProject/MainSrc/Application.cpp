#include "../Headers/shaderProgram.h"
#include "../Headers/Camera.h"
#include "../Headers/Mesh.h"
#include "../Headers/Transform.h"
#include "stb/stb_image.h"


BOG::AppInit* app = BOG::initializeApp;

int main()
{

	if (!app->createWindow("Application", 720, 480))
	{
		delete app;
		exit(1);
	}

	app->createEventManager();
	app->run();

	return 0;
}
