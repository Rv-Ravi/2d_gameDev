#include "../Headers/Transform.h"

void BOG::Transform::setPosition(const glm::vec3& position)
{
	m_position.x = position.x;
	m_position.y = position.y;
	m_position.z = position.z;

}

void BOG::Transform::setRotation(const glm::vec3& rotation)
{
	m_rotation.x = rotation.x;
	m_rotation.y = rotation.y;
	m_rotation.z = rotation.z;
}

void BOG::Transform::setScale(const glm::vec3& scale)
{
	m_scale.x = scale.x;
	m_scale.y = scale.y;
	m_scale.z = scale.z;
}

glm::mat4 BOG::Transform::getModelMat()
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.f),glm::radians(m_rotation.z),glm::vec3(0.f,0.f,1.f)) * 
						 glm::rotate(glm::mat4(1.f), glm::radians(m_rotation.y), glm::vec3(0.f, 1.f, 0.f)) *
		                 glm::rotate(glm::mat4(1.f), glm::radians(m_rotation.x), glm::vec3(1.f, 0.f, 0.f));
	return glm::translate(glm::mat4(1.f), m_position) * rotation * glm::scale(glm::mat4(1.f),m_scale);
}
