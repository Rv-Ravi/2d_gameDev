#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../Headers/appInitialize.h"

namespace BOG {
	class Transform
	{
	//members
	private:
		glm::vec3 m_position = {}, m_rotation = {}, m_scale = {1.f,1.f,1.f};

	//constructors
	public:
		Transform() = default;

	//setters and getters
	public:
		void setPosition(const glm::vec3& position);
		void setRotation(const glm::vec3& rotation);
		void setScale(const glm::vec3& scale);


		inline glm::vec3 getPosition()const { return m_position; }
		inline glm::vec3 getRotation()const { return m_rotation; }
		inline glm::vec3 getScale() const { return m_scale; }

	//methods
	public:
		glm::mat4 getModelMat();
	};
}


#endif //TRANSFORM_H

