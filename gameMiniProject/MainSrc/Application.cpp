#include "../Headers/shaderProgram.h"
#include "../Headers/Camera.h"
#include "../Headers/Mesh.h"
#include "../Headers/Transform.h"
#include "stb/stb_image.h"

uint16_t currectObjVal = 0,currentAction = 0;

glm::vec3 playerVelocity(2.5f, 6.5f, 0.f), gravity(0.f, -9.8f, 0.f);

void mvObject(std::array<BOG::Transform, 2>& models, BOG::fltPoint);
void rotateObj(std::array<BOG::Transform, 2>& models, BOG::fltPoint);
void scaleObj(std::array<BOG::Transform, 2>& models, BOG::fltPoint);
void chngObject();

int main()
{
	if (!BOG::appInitialize())
	{
		exit(1);
	}
	shaderProgram prog("D:\\Coding\\Game\\gameMiniProject\\gameMiniProject\\additionalSrc\\shaders\\simple\\simpleObj.shader");
	BOG::Camera cam_1({ 0.f, 0.0f, 0.1f });
	BOG::Mesh mesh(BOG::square, BOG::squareIndex);
	
	std::array<BOG::Transform,2> models;

	glm::vec3 lightColor(0.f, 0.f, 0.f);

	
	
	prog.bindProgram();
	prog.setUniValuefV("uColor", glm::vec3(1.f,0.f,0.f), 3);
	
	prog.unbindProgram();

	BOG::fltPoint currFramTime = 0.f, preFramTime = 0.f, FramTimePeriod,chngVal = 42.f;

	

	while (!glfwWindowShouldClose(BOG::mainWindow->getWindow()))
	{

		BOG::setColorBufer(lightColor.x, lightColor.y, lightColor.z, 1.f);
		currFramTime = glfwGetTime();
		FramTimePeriod = currFramTime - preFramTime;
		preFramTime = currFramTime;

		
		mesh.meshBind();

		prog.bindProgram();
		prog.setUniValueM("viewProj",BOG::currentCam->getViewProjMat(), 4);
		for (auto& model : models)
		{
			prog.setUniValueM("transMat", model.getModelMat(), 4);
			ErrCheck(glDrawElements(GL_TRIANGLES, BOG::squareIndex.size(), GL_UNSIGNED_INT, 0));
		}
		prog.unbindProgram();

		BOG::Mesh::meshUnbind();

		glfwSwapBuffers(BOG::mainWindow->getWindow());



		BOG::currentCam->mvCam(FramTimePeriod);
		BOG::Camera::changeCam();

		lightColor = glm::vec3(abs(sin(chngVal + 9.f)), abs(sin(chngVal - 12.f)), abs(sin(chngVal - 5.f)));
		chngVal += FramTimePeriod;

		mvObject(models, FramTimePeriod);
		rotateObj(models, FramTimePeriod);
		scaleObj(models, FramTimePeriod);
		chngObject();
		glfwPollEvents();
	}

	delete BOG::mainWindow;
	return 0;
}


void mvObject(std::array<BOG::Transform, 2>& models,BOG::fltPoint dtime) {
	if (currentAction == 0) {
		glm::vec3 position = models[currectObjVal].getPosition();
		if (BOG::keyState[GLFW_KEY_LEFT_SHIFT] == 1 && BOG::keyState[GLFW_KEY_D] == 1)
			position.x += playerVelocity.x * dtime;
		else if (BOG::keyState[GLFW_KEY_LEFT_SHIFT] == 1 && BOG::keyState[GLFW_KEY_A] == 1)
			position.x -= playerVelocity.x * dtime;
		else if (BOG::keyState[GLFW_KEY_LEFT_SHIFT] == 1 && BOG::keyState[GLFW_KEY_W] == 1)
			position.y += playerVelocity.x * dtime;
		else if (BOG::keyState[GLFW_KEY_LEFT_SHIFT] == 1 && BOG::keyState[GLFW_KEY_S] == 1)
			position.y -= playerVelocity.x * dtime;

		models[currectObjVal].setPosition(position);
	}
}

void rotateObj(std::array<BOG::Transform, 2>& models, BOG::fltPoint dtime) {

	if (currentAction == 1) {
		glm::vec3 rotation = models[currectObjVal].getRotation();

		if (BOG::keyState[GLFW_KEY_X] == 1 && BOG::keyState[GLFW_KEY_R] == 1 && BOG::keyState[GLFW_KEY_1] == 1)
			rotation.x += 1.f * dtime;
		else if (BOG::keyState[GLFW_KEY_X] == 1 && BOG::keyState[GLFW_KEY_R] == 1 && BOG::keyState[GLFW_KEY_0] == 1)
			rotation.x -= 1.f * dtime;
		else if (BOG::keyState[GLFW_KEY_Y] == 1 && BOG::keyState[GLFW_KEY_R] == 1 && BOG::keyState[GLFW_KEY_1] == 1)
			rotation.y += 1.f * dtime;
		else if (BOG::keyState[GLFW_KEY_Y] == 1 && BOG::keyState[GLFW_KEY_R] == 1 && BOG::keyState[GLFW_KEY_0] == 1)
			rotation.y -= 1.f * dtime;
		else if (BOG::keyState[GLFW_KEY_Z] == 1 && BOG::keyState[GLFW_KEY_R] == 1 && BOG::keyState[GLFW_KEY_1] == 1)
			rotation.z += 1.f * dtime;
		else if (BOG::keyState[GLFW_KEY_Z] == 1 && BOG::keyState[GLFW_KEY_R] == 1 && BOG::keyState[GLFW_KEY_0] == 1)
			rotation.z -= 1.f * dtime;

		models[currectObjVal].setRotation(rotation);
	}
}
void scaleObj(std::array<BOG::Transform, 2>& models, BOG::fltPoint dtime) {
	if (currentAction == 2) {
		glm::vec3 scale = models[currectObjVal].getScale();

		if (BOG::keyState[GLFW_KEY_X] == 1 && BOG::keyState[GLFW_KEY_S] == 1 && BOG::keyState[GLFW_KEY_1] == 1)
			scale.x += 1.f * dtime;
		else if (BOG::keyState[GLFW_KEY_X] == 1 && BOG::keyState[GLFW_KEY_S] == 1 && BOG::keyState[GLFW_KEY_0] == 1)
			scale.x -= 1.f * dtime;
		else if (BOG::keyState[GLFW_KEY_Y] == 1 && BOG::keyState[GLFW_KEY_S] == 1 && BOG::keyState[GLFW_KEY_1] == 1)
			scale.y += 1.f * dtime;
		else if (BOG::keyState[GLFW_KEY_Y] == 1 && BOG::keyState[GLFW_KEY_S] == 1 && BOG::keyState[GLFW_KEY_0] == 1)
			scale.y -= 1.f * dtime;
		else if (BOG::keyState[GLFW_KEY_Z] == 1 && BOG::keyState[GLFW_KEY_S] == 1 && BOG::keyState[GLFW_KEY_1] == 1)
			scale.z += 1.f * dtime;
		else if (BOG::keyState[GLFW_KEY_Z] == 1 && BOG::keyState[GLFW_KEY_S] == 1 && BOG::keyState[GLFW_KEY_0] == 1)
			scale.z -= 1.f * dtime;
		else if (BOG::keyState[GLFW_KEY_LEFT_SHIFT] == 1 && BOG::keyState[GLFW_KEY_S] == 1 && BOG::keyState[GLFW_KEY_1] == 1)
			scale += glm::vec3(1.f) * dtime;
		else if (BOG::keyState[GLFW_KEY_LEFT_SHIFT] == 1 && BOG::keyState[GLFW_KEY_S] == 1 && BOG::keyState[GLFW_KEY_0] == 1)
			scale -= glm::vec3(1.f) * dtime;

		models[currectObjVal].setScale(scale);
	}
}

void chngObject()
{
	if (BOG::keyState[GLFW_KEY_O] == 1)
	{
		if (BOG::keyState[GLFW_KEY_1] == 1)
			currectObjVal = 0;
		else if (BOG::keyState[GLFW_KEY_2] == 1)
			currectObjVal = 1;
	}
	if (BOG::keyState[GLFW_KEY_A] == 1)
	{
		if (BOG::keyState[GLFW_KEY_1] == 1)
			currentAction = 0;
		else if (BOG::keyState[GLFW_KEY_2] == 1)
			currentAction = 1;
		else if (BOG::keyState[GLFW_KEY_3] == 1)
			currentAction = 2;
	}
}