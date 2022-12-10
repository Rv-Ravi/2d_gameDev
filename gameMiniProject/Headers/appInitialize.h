#ifndef APP_INITIALIZE_H
#define APP_INITIALIZE_H


#include "windowCreation.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <array>
#include <vector>
#define SWIDTH 720
#define SHEIGHT 480



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


	extern std::array<uint16_t, GLFW_KEY_LAST> keyState;
	extern std::vector<vertexData> block;
	extern std::vector<uint32_t >blockIndex;
	extern std::vector<vertexData>square;
	extern std::vector<uint32_t >squareIndex;
	extern BOG::windowCreation* mainWindow;

	extern void setColorBufer(fltPoint x, fltPoint y, fltPoint z, fltPoint a);

	extern void keyEvents(GLFWwindow* window, int key, int scancode, int action, int mods);

	extern void glfwError(int id, const char* description);
	

	extern bool appInitialize();

}



#endif