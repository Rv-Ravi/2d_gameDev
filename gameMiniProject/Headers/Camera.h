#ifndef CAMERA_H
#define CAMERA_H

#include "appInitialize.h"

namespace BOG {

	class Camera
	{
	private:
		glm::vec3 m_camPos, m_camX, m_camY, m_camZ, m_camDir, m_camMaxVel = glm::vec3(6.3f), m_camSpeed;
		glm::mat4 m_viewMat, m_projMat, m_viewProjMat;

		static std::vector<BOG::Camera*> ms_camList;

		BOG::fltPoint m_zNear, m_zFar, m_right, m_left, m_top, m_bottom;

	public:
		
		//Constructors
		Camera();
		Camera(const glm::vec3& camPos, bool isOrtho = false);

		~Camera();

		//setters and getters
		void setPos(const glm::vec3& pos);
		glm::vec3 getPos();

		inline glm::mat4 getViewMat() { return m_viewMat; }
		inline glm::mat4 getProjMat() { return m_projMat; }
		inline glm::mat4 getViewProjMat() { return m_viewProjMat; }

		glm::vec3 getCamDir();

		static void changeCam();

		//methods
		void calcViewMat();
		void calcProjMat();
		void calcViewProjMat();

		void mvCam(BOG::fltPoint dtime);

	};




	extern BOG::Camera *currentCam;
}
#endif //CAMERA_H

