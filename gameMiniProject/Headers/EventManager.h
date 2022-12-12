#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "AppDataStore.h"

namespace BOG {
	class EventManager
	{
	//members
	private:
		static std::array<uint8_t, GLFW_KEY_LAST> m_keyState;
		static std::array<uint8_t, GLFW_MOUSE_BUTTON_LAST> m_mouseState;
		static double m_curPos[2];
	//constructors
	public:
		EventManager();
		virtual ~EventManager();
	//setters and getters
	public:
		uint8_t getKeyStateAt(uint16_t keyName) const;
		uint8_t getMouseStateAt(uint16_t keyName) const;
		const double* getCurPos() const;

	//methods
	public:
		static void setKeyState(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void setMouseState(GLFWwindow*, int key, int action, int mods);
		static void setCursorState(GLFWwindow* window, double xpos, double ypos);
	};
}

#endif //EVENTMANAGER_H

