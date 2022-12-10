#ifndef APP_INITIALIZE_H
#define APP_INITIALIZE_H


#include "windowCreation.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <array>
#include <vector>
#include <sstream>



#define ErrCheck(func) while (glGetError());\
		func;\
		if(BOG::getErrorLog(#func,__FILE__,__LINE__)) __debugbreak()

namespace BOG {

	typedef float fltPoint;

	extern bool getErrorLog(const char* func, const char* file, int line);

	struct vertexData {
		glm::vec3 vertexPos;
		glm::vec3 vertexCol;
		glm::vec2 texCoord;
		glm::vec3 vertexNormal;
	};

	extern std::vector<vertexData> block;
	extern std::vector<uint32_t >blockIndex;
	extern std::vector<vertexData>square;
	extern std::vector<uint32_t >squareIndex;

	extern void glfwError(int id, const char* description);


	class AppInit {
	//members
	public:
		windowCreation* m_mainWindow = nullptr;

	//constructor
	public:
		AppInit();
		~AppInit();

	//methods
	public:
		bool createWindow(const char* name, int32_t width, int32_t height, bool monitor = false);
		static void ClrUpdtBufer(const glm::vec4& color);
		void update(BOG::fltPoint dtime);
	private:
		void destryWindow();
		bool glInitializer();
	};

	extern AppInit* initializeApp;
}



#endif