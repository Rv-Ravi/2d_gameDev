#ifndef APPSCENE_H
#define APPSCENE_H


#include "PhysicsEng.h"
#include "Camera.h"
#include "EventManager.h"
#include "shaderProgram.h"

namespace BOG {

	class AppScene
	{
	
		//members
	private:
		static bool ms_gamePlay;
		BOG::fltPoint m_prevTime = 0.f; BOG::fltPoint m_currentTime = 0.f;
		static int32_t m_ptsEarned;
	public:
		std::vector<Entity> m_entityList;
		Camera m_mainCamera;
		BOG::Mesh tileMesh, blockMesh;
		Entity* m_currentEntt = nullptr;

	private:
		bool isCreated = false;
		
	//contructor
	public:
		AppScene();
		~AppScene();

	//methods
	public:
		void sceneUpdate(BOG::fltPoint dtime,EventManager* &evntMngr);
		void addTile(EventManager*& evntMngr);
		Entity* selectEntity(EventManager*& evntMngr);
		static void setGamePlay(EventManager*& evntMngr);

	private:
		void mvEntity(BOG::fltPoint dtime, EventManager*& evntMngr);
		void scaleEntity(BOG::fltPoint dtime, EventManager*& evntMngr);
		void rotateEntity(BOG::fltPoint dtime, EventManager*& evntMngr);
		void entityCheckCollision(BOG::fltPoint dtime);
		void addEnttComponent(EventManager*& evntMngr);
		void addTag(EventManager*& evntMngr);
		void removeEntt(uint16_t entityIndex);

		void mvPlayer(BOG::fltPoint dtime, EventManager*& evntMngr);
		void blockFall();
	};
	
	extern BOG::fltPoint valLerp(BOG::fltPoint dtime, BOG::fltPoint val1, BOG::fltPoint val2);
}



#endif //APPSCENE_H
