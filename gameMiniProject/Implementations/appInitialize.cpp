#include "../Headers/appInitialize.h"


namespace BOG {


	bool getErrorLog(const char* func, const char* file, int line)
	{
		while (uint32_t error = glGetError())
		{
			std::cerr << "OpenGL Error: (" << error << "):" << file << ":" << line << ":" << func << std::endl;
			return true;
		}
		return false;
	}


	std::vector<uint32_t> blockIndex =
	{
		//TOP
		0,1,2,
		0,2,3,
		//BOTTOM
		4,5,6,
		4,6,7,
		//FRONT
		8,9,10,
		8,10,11,
		//BACK
		12,13,14,
		12,14,15,
		//RIGHT
		9,10,13,
		10,14,13,
		//LEFT
		8,11,12,
		11,15,12
	};
	std::vector<BOG::vertexData> block =
	{   //POSITION	                   //COLOR					  //TEX-CO					//NORMAL
		//TOP
		{glm::vec3(-1.0f,1.0f,1.0f),   glm::vec3(1.0f,0.0f,0.0f),  glm::vec2(0.0f,1.0f),     glm::vec3(-0.33f,0.33f,0.33f)},
		{glm::vec3(1.0f,1.0f,1.0f),	  glm::vec3(0.0f,1.0f,0.0f),  glm::vec2(0.0f,0.9f),	    glm::vec3(0.33f,0.33f,0.33f)},
		{glm::vec3(1.0f,1.0f,-1.0f),	  glm::vec3(0.0f,0.0f,1.0f),  glm::vec2(1.0f,0.9f),	    glm::vec3(0.33f,0.33f,-0.33f)},
		{glm::vec3(-1.0f,1.0f,-1.0f),  glm::vec3(1.0f,1.0f,1.0f),  glm::vec2(1.0f,1.0f),	    glm::vec3(-0.33f,0.33f,-0.33f)},

		//BOTTOM
		{glm::vec3(-1.0f,-1.0f,1.0f),  glm::vec3(1.0f,0.0f,0.0f),  glm::vec2(1.0f,0.0f),	    glm::vec3(0.0f)},
		{glm::vec3(1.0f,-1.0f,1.0f),	  glm::vec3(0.0f,1.0f,0.0f),  glm::vec2(0.0f,0.0f),	    glm::vec3(0.0f)},
		{glm::vec3(1.0f,-1.0f,-1.0f),  glm::vec3(0.0f,0.0f,1.0f),  glm::vec2(1.0f,0.0f),	    glm::vec3(0.0f)},
		{glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(1.0f,1.0f,1.0f),  glm::vec2(0.0f,0.0f),	    glm::vec3(0.0f)},

		//FRONT
		{glm::vec3(-1.0f,1.0f,1.0f),   glm::vec3(1.0f,0.0f,0.0f),  glm::vec2(0.0f,1.0f),     glm::vec3(-0.33f,0.33f,0.33f)},
		{glm::vec3(1.0f,1.0f,1.0f),	  glm::vec3(0.0f,1.0f,0.0f),  glm::vec2(1.0f,1.0f),	    glm::vec3(0.33f,0.33f,0.33f)},
		{glm::vec3(1.0f,-1.0f,1.0f),	  glm::vec3(0.0f,0.0f,1.0f),  glm::vec2(1.0f,0.0f),	    glm::vec3(0.33f,-0.33f,0.33f)},
		{glm::vec3(-1.0f,-1.0f,1.0f),  glm::vec3(1.0f,1.0f,1.0f),  glm::vec2(0.0f,0.0f),	    glm::vec3(-0.33f,-0.33f,0.33f)},

		//BACK
		{glm::vec3(-1.0f,1.0f,-1.0f),   glm::vec3(1.0f,0.0f,0.0f),  glm::vec2(1.0f,1.0f),        glm::vec3(-0.33f,0.33f,-0.33f)},
		{glm::vec3(1.0f,1.0f,-1.0f),	   glm::vec3(0.0f,1.0f,0.0f),  glm::vec2(0.0f,1.0f),	    glm::vec3(0.33f,0.33f,-0.33f)},
		{glm::vec3(1.0f,-1.0f,-1.0f),   glm::vec3(0.0f,0.0f,1.0f),  glm::vec2(0.0f,0.0f),	    glm::vec3(0.33f,-0.33f,-0.33f)},
		{glm::vec3(-1.0f,-1.0f,-1.0f),  glm::vec3(1.0f,1.0f,1.0f),  glm::vec2(1.0f,0.0f),	    glm::vec3(-0.33f,-0.33f,-0.33f)}

	};



	std::vector<BOG::vertexData> square = {
	{glm::vec3(-1.0f,-1.0f,0.0f),   glm::vec3(1.0f,1.0f,1.0f),  glm::vec2(0.0f,0.0f),     glm::vec3(0.f,0.f,1.f)},
		{glm::vec3(1.0f,-1.0f,0.0f),	  glm::vec3(1.0f,1.0f,1.0f),  glm::vec2(1.0f,0.0f),	    glm::vec3(0.f,0.f,1.f)},
		{glm::vec3(1.0f,1.0f,0.0f),	  glm::vec3(1.0f,1.0f,1.0f),  glm::vec2(1.0f,1.0f),	    glm::vec3(0.f,0.f,1.f)},
		{glm::vec3(-1.0f,1.0f,0.0f),  glm::vec3(1.0f,1.0f,1.0f),  glm::vec2(0.0f,1.0f),	    glm::vec3(0.f,0.f,1.f)},

	};

	std::vector<uint32_t> squareIndex = {
			0,1,2,
			0,2,3
	};

	void glfwError(int id, const char* description)
	{
		std::cout << "(Error ID: " << id << ") = " << description << std::endl;
	}

	AppInit::AppInit()
	{
		glfwSetErrorCallback(glfwError);
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	AppInit::~AppInit()
	{
		destryWindow();
	}
	bool AppInit::createWindow(const char* name, int32_t width, int32_t height, bool monitor)
	{
		m_mainWindow = new windowCreation();
		bool rtnVal;
		if(monitor)
			rtnVal = m_mainWindow->createWindow(name, width, height, glfwGetPrimaryMonitor());
		else
			rtnVal = m_mainWindow->createWindow(name, width, height, nullptr);

		glfwMakeContextCurrent(m_mainWindow->getWindow());
		glfwSwapInterval(1);
		rtnVal = glInitializer();

		return rtnVal;
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
	void AppInit::destryWindow()
	{
		if (m_mainWindow)
			delete m_mainWindow;
	}
	void AppInit::ClrUpdtBufer(const glm::vec4& color) {
		ErrCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		ErrCheck(glClearColor(color.x, color.y, color.z, color.a));
		ErrCheck(glClearDepth(1.f));
	}

	void AppInit::update(BOG::fltPoint dtime)
	{
		ClrUpdtBufer(glm::vec4(0.2f, 0.2f, 0.2f, 1.f));
		std::stringstream title;
		title << "Application with FPS - " << int32_t(1 / dtime);
		glfwSetWindowTitle(m_mainWindow->getWindow(), title.str().c_str());
		//Other update methods



		glfwSwapBuffers(m_mainWindow->getWindow());
		glfwPollEvents();
	}

	AppInit* initializeApp = new AppInit();
}