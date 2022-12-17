#include "../Headers/windowCreation.h"



void BOG::windowCreation::destroy()
{
	glfwDestroyWindow(m_window);
	m_window = nullptr;
}

void BOG::windowCreation::setWinTitle(const char* name)
{
	glfwSetWindowTitle(m_window, name);
}

void BOG::windowCreation::setCallbacks()
{

	glfwSetKeyCallback(m_window, m_evntMngr->setKeyState);
	glfwSetMouseButtonCallback(m_window, m_evntMngr->setMouseState);
	glfwSetCursorPosCallback(m_window, m_evntMngr->setCursorState);
	glfwSetWindowSizeCallback(m_window, m_evntMngr->setWindowState);



}

GLFWwindow* BOG::windowCreation::getWindow() const
{
	return m_window;
}

bool BOG::windowCreation::createWindow(const char* name, int32_t width, int32_t height, GLFWmonitor* monitor)
{
	m_window = glfwCreateWindow(width, height, name, monitor, nullptr);
	if (!m_window)
		return false;

	m_evntMngr->setWindowState(m_window, width, height);
	return true;
}

BOG::windowCreation::~windowCreation()
{
	if (m_window != nullptr)
		this->destroy();		
}



