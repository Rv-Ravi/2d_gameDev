#include "../Headers/AppScene.h"


BOG::AppScene::AppScene()
	:m_mainCamera({0.f,0.f,1.f}), tileMesh(BOG::square, BOG::squareIndex),
	blockMesh(BOG::block, BOG::blockIndex)
{
	//this->addTile(nullptr);
}

BOG::AppScene::~AppScene()
{
}

void BOG::AppScene::addTile(EventManager* evntMngr)
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
		last->addComponent(new BOG::BoundngBoxComp(), BOG::compId::BOUNDNGBOX);
		isCreated = true;
	}
	else if (isCreated && evntMngr->getMouseStateAt(GLFW_MOUSE_BUTTON_LEFT) == 0)
		isCreated = false;
}

void BOG::AppScene::selectEntity(EventManager* evntMngr)
{
	if (!isCreated && evntMngr->getKeyStateAt(GLFW_KEY_LEFT_SHIFT) != 0 && evntMngr->getKeyStateAt(GLFW_KEY_S) != 0
		&& evntMngr->getMouseStateAt(GLFW_MOUSE_BUTTON_LEFT) == 1)
	{
		std::cout << "Clicked\n";
		const double* curVal = evntMngr->getCurPos();
		const int32_t* winSize = evntMngr->getWinSize();
		BOG::fltPoint orgVal[2] = { ((2 * curVal[0] - winSize[0]) / winSize[0]) * 16.f,  
			((2 * curVal[1] - winSize[1]) / winSize[1]) * -9.f };
		bool isSelected = false;
		for (Entity& entity : m_entityList) {
			BoundngBoxComp* bBox = (BoundngBoxComp*)entity.m_enComponents[uint16_t(BOG::compId::BOUNDNGBOX)];

			if (orgVal[0] >= bBox->m_boundLimit.x && orgVal[0] <= bBox->m_boundLimit.z && 
				orgVal[1] >= bBox->m_boundLimit.y && orgVal[1] <= bBox->m_boundLimit.w)
				isSelected = true;
			else
				isSelected = false;

			if (isSelected) {
				std::cout << entity.m_enName << " - This is been selected." << std::endl;
				break;
			}
		}
		isCreated = true;
	}
	else if (isCreated && evntMngr->getMouseStateAt(GLFW_MOUSE_BUTTON_LEFT) == 0)
		isCreated = false;
}

void BOG::AppScene::sceneUpdate(BOG::fltPoint dtime, EventManager*& evntMngr)
{
}
