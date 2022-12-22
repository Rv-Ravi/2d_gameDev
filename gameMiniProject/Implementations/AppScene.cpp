#include "../Headers/AppScene.h"

int32_t BOG::AppScene::m_ptsEarned = 0;

bool BOG::AppScene::ms_gamePlay = false;

BOG::AppScene::AppScene()
	:m_mainCamera({0.f,0.f,1.f}), tileMesh(BOG::square, BOG::squareIndex),
	blockMesh(BOG::block, BOG::blockIndex)
{
	
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
		comp->m_scale.x += dtime * 5.f;
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
	std::vector<uint16_t> rmEnttList;
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
				ridgidBodyComp* rBody1 = (ridgidBodyComp*)m_entityList[ent1].m_enComponents[uint16_t(BOG::compId::RIDBODY)];
				if (rBody && rBody1)
				{
					rBody->m_velocity.y = 0.f;
					rBody->m_isGrounded = true;
					rBody1->m_velocity.y = 0.f;
					rBody1->m_isGrounded = true;
					if (m_entityList[ent0].tagId != BOG::enTag::PLAYER)
					{
						rmEnttList.push_back(ent0);
					}
					else if (m_entityList[ent1].tagId != BOG::enTag::PLAYER)
					{

						rmEnttList.push_back(ent1);
					}
					m_ptsEarned++;
				}
				else if (rBody)
				{
					rBody->m_velocity.y = 0.f;
					rBody->m_isGrounded = true;

					if (m_entityList[ent0].tagId != BOG::enTag::PLAYER)
					{
						m_ptsEarned--;
						rmEnttList.push_back(ent0);
					}
				}
				
				collisonList.emplace_back(&m_entityList[ent0], &m_entityList[ent1]);
			}

		}

		for (uint16_t val : rmEnttList)
		{
			if(val < m_entityList.size())
			m_entityList.erase(m_entityList.begin() + val);
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

void BOG::AppScene::addTag(EventManager*& evntMngr)
{
	if (evntMngr->getKeyStateAt(GLFW_KEY_LEFT_CONTROL) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_T) == 1 &&
		evntMngr->getKeyStateAt(GLFW_KEY_1) == 1 && !Entity::setPlayer)
	{
		Entity::setPlayer = true;
		m_currentEntt->tagId = BOG::enTag::PLAYER;
	}		
	else if (evntMngr->getKeyStateAt(GLFW_KEY_LEFT_CONTROL) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_T) == 1 &&
		evntMngr->getKeyStateAt(GLFW_KEY_2) == 1)
		m_currentEntt->tagId = BOG::enTag::TILE;
	else if (evntMngr->getKeyStateAt(GLFW_KEY_LEFT_CONTROL) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_T) == 1 &&
		evntMngr->getKeyStateAt(GLFW_KEY_3) == 1)
		m_currentEntt->tagId = BOG::enTag::ENEMIES;
}

void BOG::AppScene::removeEntt(uint16_t entityIndex)
{
	m_entityList.erase(m_entityList.begin() + entityIndex);

}

void BOG::AppScene::mvPlayer(BOG::fltPoint dtime, EventManager*& evntMngr)
{
	auto player = std::find_if(m_entityList.begin(), m_entityList.end(), [&](Entity& val) {
		return val.tagId == BOG::enTag::PLAYER;
		});
	if (player != m_entityList.end())
	{
		TransformComp* tComp = (TransformComp*)player->getComponent(BOG::compId::TRANSFORM);
		ridgidBodyComp* rComp = (ridgidBodyComp*)player->getComponent(BOG::compId::RIDBODY);
		rComp->m_speed = 5.5f; glm::vec3 direction(0.f, 1.f, 0.f);
		if (evntMngr->getKeyStateAt(GLFW_KEY_RIGHT) == 1 && rComp->m_isGrounded)
		{
			rComp->m_velocity.x = valLerp(dtime, rComp->m_velocity.x,rComp->m_speed);
			
		}
		else if (evntMngr->getKeyStateAt(GLFW_KEY_LEFT) == 1 && rComp->m_isGrounded) {
			rComp->m_velocity.x = valLerp(dtime, rComp->m_velocity.x, -rComp->m_speed);
		}
		else {
			rComp->m_velocity.x = valLerp(dtime, rComp->m_velocity.x, 0.f);
		}
		tComp->m_position.x += rComp->m_velocity.x * dtime;
		if (evntMngr->getKeyStateAt(GLFW_KEY_SPACE) == 1 && rComp->m_isGrounded)
		{
			rComp->m_velocity.y = 6.0f;
			rComp->m_isGrounded = false;
			tComp->m_position.y += rComp->m_velocity.y * dtime;
		}
	}
}

void BOG::AppScene::blockFall()
{
	m_currentTime = glfwGetTime();
	BOG::fltPoint timeDiff = m_currentTime - m_prevTime;
	
	if (timeDiff > 2.f)
	{
		std::srand(uint32_t(m_currentTime));
		BOG::fltPoint rndPt = (std::rand() % 32) - 16.f;


		std::stringstream ss;
		ss << "Block-" << m_entityList.size();
		m_entityList.emplace_back(ss.str().c_str());

		auto last = m_entityList.end() - 1;
		last->addComponent(new MeshComp(&tileMesh), compId::MESH);
		last->addComponent(new TransformComp(glm::vec3(rndPt,11.f,0.f)), compId::TRANSFORM);
		last->addComponent(new MaterialComp(glm::vec3(0.2f, 1.f, 0.2f)), compId::MATERIAL);
		last->isMesh = true;
		last->addComponent(new BoxBoundComp(), BOG::compId::BOUNDNGBOX);
		last->addComponent(new ridgidBodyComp(), BOG::compId::RIDBODY);

		m_prevTime = m_currentTime;

	}
}

void BOG::AppScene::sceneUpdate(BOG::fltPoint dtime, EventManager*& evntMngr)
{
	if (!ms_gamePlay && m_currentEntt)
	{
		this->mvEntity(dtime, evntMngr);
		this->scaleEntity(dtime, evntMngr);
		this->addEnttComponent(evntMngr);
		this->addTag(evntMngr);
	}
	else if (ms_gamePlay)
	{
		blockFall();
		mvPlayer(dtime, evntMngr);
		entityCheckCollision(dtime);

		std::cout << "Current match point is : " << m_ptsEarned << std::endl;
	}
}

BOG::fltPoint BOG::valLerp(BOG::fltPoint dtime, BOG::fltPoint val1, BOG::fltPoint val2)
{
	return (val2 - val1) * dtime + val1;
}
