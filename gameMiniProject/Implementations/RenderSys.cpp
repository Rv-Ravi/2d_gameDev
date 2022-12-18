#include "../Headers/RenderSys.h"

BOG::RenderSys::RenderSys()
	:program("D:\\Coding\\Game\\gameMiniProject\\gameMiniProject\\additionalSrc\\shaders\\simple\\simpleObj.shader")
{
}

BOG::RenderSys::~RenderSys()
{
}

void BOG::RenderSys::renderScene(AppScene* scene, BOG::fltPoint dtime, EventManager*& evntMngr)
{
	BOG::Transform transform;
	scene->sceneUpdate(dtime, evntMngr);
	for (BOG::Entity& entity : scene->m_entityList)
	{
		MeshComp* comp1 = nullptr;
		if (entity.isMesh)
		{
			
			MeshComp* comp1 = (MeshComp*)entity.getComponent(BOG::compId::MESH);
			TransformComp* comp2 = (TransformComp*)entity.getComponent(BOG::compId::TRANSFORM);
			MaterialComp* comp3 = (MaterialComp*)entity.getComponent(BOG::compId::MATERIAL);
			

			comp1->m_mesh->meshBind();
			program.bindProgram();

			program.setUniValueM("transMat", transform.getModelMat(comp2->m_position,comp2->m_rotation,comp2->m_scale), 4);
			program.setUniValueM("viewProj", scene->m_mainCamera.getViewProjMat(), 4);
			program.setUniValuefV("uColor", comp3->m_color, 3);

			ErrCheck(glDrawElements(GL_TRIANGLES, comp1->m_mesh->getObjIndexLen(), GL_UNSIGNED_INT, 0));

			program.unbindProgram();
		}

	}
}
