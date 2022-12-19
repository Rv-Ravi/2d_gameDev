#include "../Headers/AppScene.h"


bool BOG::AppScene::ms_gamePlay = false;

BOG::AppScene::AppScene()
	:m_mainCamera({0.f,0.f,1.f}), tileMesh(BOG::square, BOG::squareIndex),
	blockMesh(BOG::block, BOG::blockIndex)
{
	//this->addTile(nullptr);
}

BOG::AppScene::~AppScene()
{
}

void BOG::AppScene::addTile(EventManager*& evntMngr)
{
	if (!isCreated && evntMngr->getKeyStateAt(GLFW_KEY_LEFT_SHIFT) != 0 && evntMngr->getKeyStateAt(GLFW_KEY_T) != 0
		&& evntMngr->getMouseStateAt(GLFW_MOUSE_BUTTON_LEFT) == 1)
	{

		std::stringstream ss;
		ss << "Tile-" << m_entityList.size();
		m_entityList.emplace_back(ss.str().c_str());

		const double* curVal = evntMngr->getCurPos();
		const int32_t* winSize = evntMngr->getWinSize();

		auto last = m_entityList.end() - 1;
		last->addComponent(new MeshComp(&tileMesh), compId::MESH);
		last->addComponent(new TransformComp(glm::vec3(((2 * curVal[0] - winSize[0]) / winSize[0]) * 16.f
			, ((2 * curVal[1] - winSize[1]) / winSize[1]) * -9.f
			, 0.f)), compId::TRANSFORM);
		last->addComponent(new MaterialComp(glm::vec3(0.2f, 1.f, 0.2f)), compId::MATERIAL);
		last->isMesh = true;
		last->addComponent(new BoxBoundComp(), BOG::compId::BOUNDNGBOX);
		isCreated = true;
		this->m_currentEntt = &(*last);
	}
	else if (isCreated && evntMngr->getMouseStateAt(GLFW_MOUSE_BUTTON_LEFT) == 0)
		isCreated = false;
}

BOG::Entity* BOG::AppScene::selectEntity(EventManager* &evntMngr)
{
	if (!isCreated && evntMngr->getKeyStateAt(GLFW_KEY_LEFT_SHIFT) != 0 && evntMngr->getKeyStateAt(GLFW_KEY_S) != 0
		&& evntMngr->getMouseStateAt(GLFW_MOUSE_BUTTON_LEFT) == 1)
	{
		const double* curVal = evntMngr->getCurPos();
		const int32_t* winSize = evntMngr->getWinSize();
		glm::vec2 orgVal = { ((2 * curVal[0] - winSize[0]) / winSize[0]) * 16.f,
			((2 * curVal[1] - winSize[1]) / winSize[1]) * -9.f };
		bool isSelected = false;
		for (Entity& entity : m_entityList) {
			if (PhysicsEng::ptCollision(orgVal, entity))
			{
				isCreated = true;
				return &entity;
			}
				
		}
		isCreated = true;
		return nullptr;
	}
	else if (isCreated && evntMngr->getMouseStateAt(GLFW_MOUSE_BUTTON_LEFT) == 0)
		isCreated = false;

	return this->m_currentEntt;
}

void BOG::AppScene::setGamePlay(EventManager*& evntMngr)
{
	if (evntMngr->getKeyStateAt(GLFW_KEY_LEFT_SHIFT) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_G) == 1
		&& evntMngr->getKeyStateAt(GLFW_KEY_1) == 1)
		ms_gamePlay = true;
	else if (evntMngr->getKeyStateAt(GLFW_KEY_LEFT_SHIFT) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_G) == 1
		&& evntMngr->getKeyStateAt(GLFW_KEY_0) == 1)
		ms_gamePlay = false;
}

void BOG::AppScene::mvEntity(BOG::fltPoint dtime, EventManager*& evntMngr)
{
	TransformComp* comp = (TransformComp*)m_currentEntt->m_enComponents[uint16_t(BOG::compId::TRANSFORM)];
	if (evntMngr->getKeyStateAt(GLFW_KEY_T) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_X) == 1
		&& evntMngr->getKeyStateAt(GLFW_KEY_1) == 1)
	{
		comp->m_position.x += dtime;
	}
	else if (evntMngr->getKeyStateAt(GLFW_KEY_T) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_X) == 1
		&& evntMngr->getKeyStateAt(GLFW_KEY_0) == 1)
	{
		comp->m_position.x -= dtime;
	}
	else if (evntMngr->getKeyStateAt(GLFW_KEY_T) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_Y) == 1
		&& evntMngr->getKeyStateAt(GLFW_KEY_1) == 1)
	{
		comp->m_position.y += dtime;
	}
	else if (evntMngr->getKeyStateAt(GLFW_KEY_T) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_Y) == 1
		&& evntMngr->getKeyStateAt(GLFW_KEY_0) == 1)
	{
		comp->m_position.y -= dtime;
	}

}

void BOG::AppScene::scaleEntity(BOG::fltPoint dtime, EventManager*& evntMngr)
{
	TransformComp* comp = (TransformComp*)m_currentEntt->m_enComponents[uint16_t(BOG::compId::TRANSFORM)];
	if (evntMngr->getKeyStateAt(GLFW_KEY_LEFT_SHIFT) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_S) == 1
		&& evntMngr->getKeyStateAt(GLFW_KEY_1) == 1)
	{
		comp->m_scale += glm::vec3(dtime, dtime, 0.f);
	}
	else if (evntMngr->getKeyStateAt(GLFW_KEY_LEFT_SHIFT) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_S) == 1
		&& evntMngr->getKeyStateAt(GLFW_KEY_0) == 1)
	{
		comp->m_scale -= glm::vec3(dtime, dtime, 0.f);
	}
	else if (evntMngr->getKeyStateAt(GLFW_KEY_S) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_X) == 1
		&& evntMngr->getKeyStateAt(GLFW_KEY_1) == 1)
	{
		comp->m_scale.x += dtime;
	}
	else if (evntMngr->getKeyStateAt(GLFW_KEY_S) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_X) == 1
		&& evntMngr->getKeyStateAt(GLFW_KEY_0) == 1)
	{
		comp->m_scale.x -= dtime;
	}
	else if (evntMngr->getKeyStateAt(GLFW_KEY_S) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_Y) == 1
		&& evntMngr->getKeyStateAt(GLFW_KEY_1) == 1)
	{
		comp->m_scale.y += dtime;
	}
	else if (evntMngr->getKeyStateAt(GLFW_KEY_S) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_Y) == 1
		&& evntMngr->getKeyStateAt(GLFW_KEY_0) == 1)
	{
		comp->m_scale.y -= dtime;
	}
}

void BOG::AppScene::rotateEntity(BOG::fltPoint dtime, EventManager*& evntMngr)
{
}

void BOG::AppScene::entityCheckCollision(BOG::fltPoint dtime)
{
	std::vector<std::pair<Entity*, Entity*>> collisonList;
	for (int ent0 = 0;ent0 < m_entityList.size();ent0++)
	{	
		BOG::PhysicsEng::gravityResponse(dtime, m_entityList[ent0]);

		ridgidBodyComp* rBody = (ridgidBodyComp*)m_entityList[ent0].m_enComponents[uint16_t(BOG::compId::RIDBODY)];
		for (int ent1 = 0; rBody && !rBody->m_isKinematic && ent1 < m_entityList.size(); ent1++)
		{
			if (std::find_if(collisonList.begin(), collisonList.end(), [&](std::pair<Entity*, Entity*> val) {
				return (&m_entityList[ent0] == val.second && &m_entityList[ent1] == val.first);
				}) != collisonList.end())
				continue;
				
			if (&m_entityList[ent0] != &m_entityList[ent1] && BOG::PhysicsEng::boxCollision(m_entityList[ent0], m_entityList[ent1]))
			{
				//std::cout << m_entityList[ent0].m_enName << " Collided with " << m_entityList[ent1].m_enName << std::endl;
				collisonList.emplace_back(&m_entityList[ent0], &m_entityList[ent1]);

			}
		}
	}
}

void BOG::AppScene::addEnttComponent(EventManager*& evntMngr)
{
	if (evntMngr->getKeyStateAt(GLFW_KEY_C) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_A) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_5) == 1)
	{
		Component* tmpComp = new ridgidBodyComp();
		if (!m_currentEntt->addComponent(tmpComp, BOG::compId::RIDBODY)) delete tmpComp;
	}

}

void BOG::AppScene::sceneUpdate(BOG::fltPoint dtime, EventManager*& evntMngr)
{
	if (!ms_gamePlay && m_currentEntt)
	{
		this->mvEntity(dtime, evntMngr);
		this->scaleEntity(dtime, evntMngr);
		this->addEnttComponent(evntMngr);
	}
	else if (ms_gamePlay)
	{
		entityCheckCollision(dtime);
	}
}
