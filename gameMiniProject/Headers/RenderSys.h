#ifndef  RENDERSYS_H
#define RENDERSYS_H


#include "AppScene.h"

namespace BOG {
	class RenderSys
	{
		//members
	private:
		shaderProgram program;

	//constructor
	public:
		RenderSys();
		~RenderSys();

	//methods
	public:
		void renderScene(AppScene* scene, BOG::fltPoint dtime, EventManager*& evntMngr);

	};
}


#endif //RENDERSYS_H

