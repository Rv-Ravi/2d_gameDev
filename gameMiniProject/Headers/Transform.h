#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../Headers/appDataStore.h"

namespace BOG {
	class Transform
	{
	//members

	//constructors
	public:
		Transform() = default;

	//methods
	public:
		glm::mat4 getModelMat(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	};
}


#endif //TRANSFORM_H

