#include "../Headers/PhysicsEng.h"

bool BOG::Entity::setPlayer = false;

BOG::PhysicsEng::PhysicsEng()
{
}

BOG::PhysicsEng::~PhysicsEng()
{
}

glm::vec3 BOG::PhysicsEng::m_gravity = { 0.f,-9.8f,0.f };

void BOG::PhysicsEng::gravityResponse(BOG::fltPoint dtime, Entity& entity)
{
	ridgidBodyComp* rBody = (ridgidBodyComp*)entity.m_enComponents[uint16_t(BOG::compId::RIDBODY)];
	TransformComp* tComp = (TransformComp*)entity.m_enComponents[uint16_t(BOG::compId::TRANSFORM)];

	if (rBody && !rBody->m_isKinematic && rBody->m_gravity)
	{
		glm::vec3 FA = m_gravity * rBody->m_mass;
		tComp->m_position += rBody->m_velocity * dtime;
		rBody->m_velocity += FA * dtime;
	}
}

bool BOG::PhysicsEng::ptCollision(const glm::vec2& pt, Entity& entity)
{
	BoxBoundComp* bBox = (BoxBoundComp*)entity.m_enComponents[uint16_t(BOG::compId::BOUNDNGBOX)];
	TransformComp* tComp = (TransformComp*)entity.m_enComponents[uint16_t(BOG::compId::TRANSFORM)];

	glm::vec3 orgTrans = tComp->m_position + bBox->m_centerPt;
	glm::vec3 orgMin = -(bBox->m_size * tComp->m_scale) + orgTrans;
	glm::vec3 orgMax = (bBox->m_size * tComp->m_scale) + orgTrans;

	if (pt.x >= orgMin.x && pt.x <= orgMax.x &&
		pt.y >= orgMin.y && pt.y <= orgMax.y)
	{
		return true;
	}
	return false;
}

bool BOG::PhysicsEng::boxCollision(Entity& entity1, Entity& entity2)
{

	BoxBoundComp* EnBComp1 = (BoxBoundComp*)entity1.m_enComponents[uint16_t(BOG::compId::BOUNDNGBOX)];
	TransformComp* EnTComp1 = (TransformComp*)entity1.m_enComponents[uint16_t(BOG::compId::TRANSFORM)];
	ridgidBodyComp* EnRComp1 = (ridgidBodyComp*)entity1.m_enComponents[uint16_t(BOG::compId::RIDBODY)];

	BoxBoundComp* EnBComp2 = (BoxBoundComp*)entity2.m_enComponents[uint16_t(BOG::compId::BOUNDNGBOX)];
	TransformComp* EnTComp2 = (TransformComp*)entity2.m_enComponents[uint16_t(BOG::compId::TRANSFORM)];
	ridgidBodyComp* EnRComp2 = (ridgidBodyComp*)entity2.m_enComponents[uint16_t(BOG::compId::RIDBODY)];

	glm::vec3 orgTrans1 = EnTComp1->m_position + EnBComp1->m_centerPt;
	glm::vec3 orgMin1 = -(EnBComp1->m_size * EnTComp1->m_scale) + orgTrans1;
	glm::vec3 orgMax1 = (EnBComp1->m_size * EnTComp1->m_scale) + orgTrans1;

	glm::vec3 orgTrans2 = EnTComp2->m_position + EnBComp2->m_centerPt;
	glm::vec3 orgMin2 = -(EnBComp2->m_size * EnTComp2->m_scale) + orgTrans2;
	glm::vec3 orgMax2 = (EnBComp2->m_size * EnTComp2->m_scale) + orgTrans2;

	if (!(orgMin1.x >= orgMin2.x && orgMin1.x <= orgMax2.x) && 
		!(orgMax1.x >= orgMin2.x && orgMax1.x <= orgMax2.x))
	{
		return false;
	}
	if (!(orgMin1.y >= orgMin2.y && orgMin1.y <= orgMax2.y) &&
		!(orgMax1.y >= orgMin2.y && orgMax1.y <= orgMax2.y))
	{
		return false;
	}



	EnRComp1->m_velocity.y = 0.f;
	EnRComp1->m_isGrounded = true;
	return true;
}
