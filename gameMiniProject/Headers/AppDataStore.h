#ifndef APPDATASTORE_H
#define APPDATASTORE_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <array>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>


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



}

#endif //APPDATASTORE_H

