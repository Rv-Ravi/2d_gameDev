#ifndef WINDOW_CREATION_H
#define WINDOW_CREATION_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace BOG
{

	class windowCreation
	{
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
		GLFWwindow* getWindow(); 
	};

}


#endif //WINDOW_CREATION_H