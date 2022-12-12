#include "../Headers/Camera.h"

namespace BOG {

	std::vector<BOG::Camera*> BOG::Camera::ms_camList;
	glm::vec3 lerp(float alpha, const glm::vec3& a, const glm::vec3& b)
	{
		return { (b.x - a.x) * alpha + a.x, (b.y - a.y) * alpha + a.y, (b.z - a.z) * alpha + a.z };
	}


	Camera::Camera()
		:m_camPos(0.f), m_camX(1.f, 0.f, 0.f), m_camY(0.f, 1.f, 0.f), m_camZ(0.f, 0.f, 1.f), m_camDir(-m_camZ),
		m_right(16.f), m_left(-16.f), m_top(9.f), m_bottom(-9.f),
		m_viewMat(1.f), m_projMat(1.f), m_viewProjMat(1.f), m_camSpeed(0.f), m_zNear(0.01f), m_zFar(10.f)
	{
		if (ms_camList.size() == 0)
		{
			ms_camList.reserve(5);
			BOG::currentCam = this;
		}
			
		if (ms_camList.size() < ms_camList.capacity()) ms_camList.emplace_back(this);
		calcViewMat();
		calcProjMat();
		calcViewProjMat();

	}

	Camera::Camera(const glm::vec3& camPos, bool isOrhto)
		:m_camPos(camPos), m_camX(1.f, 0.f, 0.f), m_camY(0.f, 1.f, 0.f), m_camZ(0.f, 0.f, 1.f), m_camDir(-m_camZ),
		m_right(16.f), m_left(-16.f), m_top(9.f), m_bottom(-9.f),
		m_viewMat(1.f), m_projMat(1.f), m_viewProjMat(1.f), m_camSpeed(0.f), m_zNear(0.01f), m_zFar(10.f)
	{
		if (ms_camList.size() == 0)
		{
			ms_camList.reserve(5);
			BOG::currentCam = this;
		}
			
		if (ms_camList.size() < ms_camList.capacity()) ms_camList.emplace_back(this);
		calcViewMat();
		calcProjMat();
		calcViewProjMat();
	}


	Camera::~Camera()
	{
		std::vector<BOG::Camera*>::iterator ite = std::find(ms_camList.begin(), ms_camList.end(), this);
		if (ite != ms_camList.end())
		{
			*ite = nullptr;
			ms_camList.erase(ite);
		}
	}

	void Camera::calcViewMat() {
		if (m_camZ != -m_camDir)
		{
			m_camZ = glm::normalize(m_camZ);
			m_camX = glm::normalize(glm::cross(m_camY, m_camZ));
			m_camY = glm::cross(m_camZ, m_camX);
			m_camDir = -m_camZ;
		}

		m_viewMat[0][0] = m_camX.x; m_viewMat[1][0] = m_camX.y; m_viewMat[2][0] = m_camX.z;
		m_viewMat[0][1] = m_camY.x; m_viewMat[1][1] = m_camY.y; m_viewMat[2][1] = m_camY.z;
		m_viewMat[0][2] = m_camZ.x; m_viewMat[1][2] = m_camZ.y; m_viewMat[2][2] = m_camZ.z;
		m_viewMat[3][0] = -glm::dot(m_camX, m_camPos);
		m_viewMat[3][1] = -glm::dot(m_camY, m_camPos);
		m_viewMat[3][2] = -glm::dot(m_camZ, m_camPos);
	}

	void Camera::calcProjMat() {
		m_projMat = glm::ortho(m_left,m_right,m_bottom,m_top,m_zNear,m_zFar);

	}

	void Camera::setPos(const glm::vec3& pos)
	{
		m_camPos.x = pos.x;
		m_camPos.y = pos.y;
		m_camPos.z = pos.z;
	}

	glm::vec3 Camera::getPos()
	{
		return m_camPos;
	}

	void Camera::changeCam() {

	}

	void Camera::calcViewProjMat()
	{
		m_viewProjMat = m_projMat * m_viewMat;
	}

	glm::vec3 Camera::getCamDir()
	{
		return m_camDir;
	}

	void Camera::mvCam(BOG::fltPoint dtime)
	{
		calcViewMat();
		calcViewProjMat();

	}
	BOG::Camera* BOG::currentCam = nullptr;
}