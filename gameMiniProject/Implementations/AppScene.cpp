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
			, 0.f)), compId::TRANFORM);
		last->addComponent(new MaterialComp(glm::vec3(0.2f, 1.f, 0.2f)), compId::MATERIAL);
		last->isMesh = true;
		isCreated = true;

	}
	else if (isCreated && evntMngr->getMouseStateAt(GLFW_MOUSE_BUTTON_LEFT) == 0)
		isCreated = false;
}

void BOG::AppScene::selectEntity(EventManager* evntMngr)
{
	
}

void BOG::AppScene::sceneUpdate(BOG::fltPoint dtime, EventManager*& evntMngr)
{
}
