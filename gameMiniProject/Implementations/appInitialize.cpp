#include "../Headers/appInitialize.h"


namespace BOG {

	AppInit::AppInit()
	{
		this->glfwInitilizer();
		this->m_mainWindow = new windowCreation();
		this->m_deltaTime = new delTime();
	}
	AppInit::~AppInit()
	{
		this->destroy();
	}
	bool AppInit::createWindow(const char* name, int32_t width, int32_t height, bool monitor)
	{
		bool rtnVal;
		if(monitor)
			rtnVal = m_mainWindow->createWindow(name, width, height, glfwGetPrimaryMonitor());
		else
			rtnVal = m_mainWindow->createWindow(name, width, height, nullptr);

		glfwMakeContextCurrent(m_mainWindow->getWindow());
		glfwSwapInterval(1);
		rtnVal = glInitializer();
		m_appScene = new AppScene();
		m_appRenderer = new RenderSys();
		return rtnVal;
	}
	void AppInit::createEventManager(EventManager* mngr)
	{
		if (mngr == nullptr)
			this->m_mainWindow->m_evntMngr = new EventManager();
		else
			this->m_mainWindow->m_evntMngr = mngr;

		m_mainWindow->setCallbacks();
	}
	bool AppInit::glInitializer()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "Unable to initialize GLAD OPENGL. please check the code.\n";
			glfwDestroyWindow(m_mainWindow->getWindow());
			glfwTerminate();
			return false;
		}
		
		glfwSetFramebufferSizeCallback(m_mainWindow->getWindow(), [](GLFWwindow* window, int width, int height) {
			ErrCheck(glViewport(0, 0, width, height));
			});
		ErrCheck(glEnable(GL_DEPTH_TEST));

		return true;
	}
	void AppInit::glfwInitilizer()
	{
		glfwSetErrorCallback(glfwError);
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	void AppInit::destroy()
	{
		if (m_mainWindow) delete m_mainWindow;
		if (m_deltaTime) delete m_deltaTime;
	}
	void AppInit::ClrUpdtBufer(const glm::vec4& color) {
		ErrCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		ErrCheck(glClearColor(color.x, color.y, color.z, color.a));
		ErrCheck(glClearDepth(1.f));
	}

	GLFWwindow* AppInit::getWindow() const
	{
		return m_mainWindow->getWindow();
	}

	//bool AppInit::isWinClose() const
	//{
	//	return glfwWindowShouldClose(m_mainWindow->getWindow());
	//}

	void AppInit::run()
	{
		
		while (!glfwWindowShouldClose(m_mainWindow->getWindow()))
		{
			this->update();
			this->checkEvent();
		}
			
	}

	void AppInit::update()
	{
		m_deltaTime->update();
		BOG::fltPoint dtime = m_deltaTime->getFramTm();
		this->ClrUpdtBufer(glm::vec4(0.2f, 0.2f, 0.2f, 1.f));
		//Other update methods

		m_appRenderer->renderScene(m_appScene, dtime, m_mainWindow->m_evntMngr);

		glfwSwapBuffers(m_mainWindow->getWindow());

	}

	void AppInit::checkEvent()
	{
		m_appScene->addTile(m_mainWindow->m_evntMngr);
		m_appScene->selectEntity(m_mainWindow->m_evntMngr);
		glfwPollEvents();
	}

	AppInit* initializeApp = new AppInit();
}