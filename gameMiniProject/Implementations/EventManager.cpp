#include "../Headers/EventManager.h"


std::array<uint8_t, GLFW_KEY_LAST> BOG::EventManager::m_keyState = { 0 };
std::array<uint8_t, GLFW_MOUSE_BUTTON_LAST> BOG::EventManager::m_mouseState = { 0 };
double BOG::EventManager::m_curPos[2] = { 0 };
int32_t BOG::EventManager::m_winSize[2] = { 0 };


BOG::EventManager::EventManager()
{
}

BOG::EventManager::~EventManager()
{
	
}

uint8_t BOG::EventManager::getKeyStateAt(uint16_t keyName) const
{
	if (keyName <= GLFW_KEY_LAST)return m_keyState[keyName];
	return 0;
}

uint8_t BOG::EventManager::getMouseStateAt(uint16_t keyName) const
{
	if (keyName <= GLFW_MOUSE_BUTTON_LAST)return m_mouseState[keyName];
	return 0;
}

const double* BOG::EventManager::getCurPos() const
{
	return m_curPos;
}

const int32_t* BOG::EventManager::getWinSize() const
{
	return m_winSize;
}

void BOG::EventManager::setKeyState(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_RELEASE)
		m_keyState[key] = action;
}

void BOG::EventManager::setMouseState(GLFWwindow*, int key, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_RELEASE)
		m_mouseState[key] = action;
}

void BOG::EventManager::setCursorState(GLFWwindow* window, double xpos, double ypos)
{
	m_curPos[0] = xpos;
	m_curPos[1] = ypos;
}

void BOG::EventManager::setWindowState(GLFWwindow* window, int32_t xpos, int32_t ypos)
{
	m_winSize[0] = xpos;
	m_winSize[1] = ypos;
}
