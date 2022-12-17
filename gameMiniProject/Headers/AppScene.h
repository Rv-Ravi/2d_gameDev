#ifndef APPSCENE_H
#define APPSCENE_H


#include "EnCmpSys.h"
#include "Camera.h"
#include "EventManager.h"
#include "shaderProgram.h"

namespace BOG {

	class AppScene
	{
		//members
	public:
		std::vector<Entity> m_entityList;
		Camera m_mainCamera;
		BOG::Mesh tileMesh, blockMesh;
		bool isCreated = false;
		Entity* m_currentEntt = nullptr;
		
	//contructor
	public:
		AppScene();
		~AppScene();

	//methods
	public:
		void sceneUpdate(BOG::fltPoint dtime,EventManager* &evntMngr);
		void addTile(EventManager* evntMngr);
		void selectEntity(EventManager* evntMngr);
	};

}



#endif //APPSCENE_H
