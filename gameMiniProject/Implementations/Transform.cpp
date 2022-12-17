#include "../Headers/Transform.h"

glm::mat4 BOG::Transform::getModelMat(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	return glm::translate(glm::mat4(1.f), position) * glm::rotate(glm::mat4(1.f), glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f))
		* glm::scale(glm::mat4(1.f),scale);
}
