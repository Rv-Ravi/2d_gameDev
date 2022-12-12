#include "../Headers/AppScene.h"


BOG::AppScene::AppScene()
	:m_mainCamera({0.f,0.f,1.f}), tileMesh(BOG::square, BOG::squareIndex),
	blockMesh(BOG::block, BOG::blockIndex),prog("D:\\Coding\\Game\\gameMiniProject\\gameMiniProject\\additionalSrc\\shaders\\simple\\simpleObj.shader")
{
	this->addTile(nullptr);
}

BOG::AppScene::~AppScene()
{
}

void BOG::AppScene::addTile(EventManager* evntMngr)
{
	//if (evntMngr->getKeyStateAt(GLFW_KEY_LEFT_SHIFT) == 1 && evntMngr->getKeyStateAt(GLFW_KEY_T) == 1)
	//{
		std::stringstream ss;
		ss << "Tile-" << m_entityList.size();
		m_entityList.emplace_back(ss.str().c_str());

		auto last = m_entityList.end() - 1;
		last->addComponent(new TransformComp(), compId::TRANFORM);
		last->addComponent(new MeshComp(&tileMesh), compId::MESH);
	//}
}

void BOG::AppScene::sceneUpdate(BOG::fltPoint dtime, EventManager*& evntMngr)
{
	for (auto entity : m_entityList)
	{
		MeshComp* comp1 = (MeshComp*)entity.getComponent(1);
		TransformComp* comp2 = (TransformComp*)entity.getComponent(0);

		comp1->m_mesh->meshBind();
		prog.bindProgram();

		prog.setUniValueM("transMat", glm::mat4(1.f), 4);
		prog.setUniValueM("viewProj", m_mainCamera.getViewProjMat(), 4);
		prog.setUniValuefV("uColor", glm::vec3(1.f), 3);

		ErrCheck(glDrawElements(GL_TRIANGLES, comp1->m_mesh->getObjIndexLen(), GL_UNSIGNED_INT, 0));

		prog.unbindProgram();
	}

}
