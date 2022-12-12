#ifndef APP_INITIALIZE_H
#define APP_INITIALIZE_H


#include "windowCreation.h"
#include "deltaTime.h"
#include "AppScene.h"

namespace BOG {

	class AppInit {
	//members
	private:
		windowCreation* m_mainWindow = nullptr;
		delTime* m_deltaTime = nullptr;
		AppScene* m_appScene = nullptr;
	//constructor
	public:
		AppInit();
		~AppInit();

	//methods
	public:
		bool createWindow(const char* name, int32_t width, int32_t height, bool monitor = false);
		void createEventManager(EventManager* mngr = nullptr);
		static void ClrUpdtBufer(const glm::vec4& color);
		GLFWwindow* getWindow() const;
		//bool isWinClose() const;
		void run();
	private:
		void destroy();
		bool glInitializer();
		void glfwInitilizer();
		void update();
		void checkEvent();
	};

	extern AppInit* initializeApp;
}



#endif