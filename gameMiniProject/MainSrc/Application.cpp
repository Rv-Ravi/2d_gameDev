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

	BOG::fltPoint currFramTime = 0.f, preFramTime = 0.f, FramTimePeriod,chngVal = 42.f;

	

	while (!glfwWindowShouldClose(app->m_mainWindow->getWindow()))
	{

		currFramTime = glfwGetTime();
		FramTimePeriod = currFramTime - preFramTime;
		preFramTime = currFramTime;


		app->update(FramTimePeriod);
	}

	return 0;
}
