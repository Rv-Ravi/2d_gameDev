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
	private:
		std::vector<Entity> m_entityList;
		Camera m_mainCamera;
		BOG::Mesh tileMesh, blockMesh;
		shaderProgram prog;
	//contructor
	public:
		AppScene();
		~AppScene();

	//methods
	private:
		void addTile(EventManager* evntMngr);

	public:
		void sceneUpdate(BOG::fltPoint dtime,EventManager* &evntMngr);
	};

}



#endif //APPSCENE_H
