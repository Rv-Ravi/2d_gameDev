#ifndef PHYSICSENG_H
#define PHYSICSENG_H

#include "EnCmpSys.h"

namespace BOG {
	class PhysicsEng
	{

	public:
		static glm::vec3 m_gravity;
		//constructor
	public:
		PhysicsEng();
		~PhysicsEng();

	//methods
	public:
		static void gravityResponse(BOG::fltPoint dtime, Entity& entity);
		static bool ptCollision(const glm::vec2& pt, Entity& entity);
		static bool boxCollision(Entity& entity1, Entity& entity2);
	};
}

#endif PHYSICSENG_H