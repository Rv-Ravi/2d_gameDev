#ifndef WINDOW_CREATION_H
#define WINDOW_CREATION_H

#include "EventManager.h"

namespace BOG
{

	class windowCreation
	{
	//methods
	public:
		EventManager* m_evntMngr = nullptr;
	private:
		GLFWwindow* m_window = nullptr;
	public:
		
		windowCreation() = default;
		~windowCreation();
	//methods
	public:
		bool createWindow(const char* name, int32_t width, int32_t height, GLFWmonitor* monitor);
		void destroy();
		void setWinTitle(const char* name);
		void setCallbacks();
		GLFWwindow* getWindow() const; 
	};

}


#endif //WINDOW_CREATION_H