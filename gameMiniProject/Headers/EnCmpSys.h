#ifndef ENCMPSYS_H
#define ENCMPSYS_H

#include "Mesh.h"
#include "Transform.h"

namespace BOG {

	enum class enTag :uint16_t {
		NONE = 0,PLAYER,TILE
	};

	enum class compId :uint16_t {
		MESH = 0,TRANSFORM,MATERIAL,BOUNDNGBOX,BOUNDNGCIRCLE,RIDBODY
	};

	struct Component {
		uint16_t m_compId;
	};

	struct TransformComp : public  Component{

		glm::vec3 m_position = { 0.f,0.f,0.f };
		glm::vec3 m_rotation = { 0.f,0.f,0.f };
		glm::vec3 m_scale = { 1.f,1.f,1.f };

		TransformComp(const glm::vec3& position = {0.f,0.f,0.f}) : m_position(position) {}
	};

	struct MaterialComp : public Component {
		glm::vec3 m_color = { 1.f,1.f,1.f };

		MaterialComp(const glm::vec3& color)
			:m_color(color)
		{}
	};

	struct MeshComp : public Component {
		BOG::Mesh* m_mesh;
		MeshComp(BOG::Mesh* mesh) {
			m_mesh = mesh;
		}
	};

	struct BoxBoundComp : public Component {
		glm::vec3 m_centerPt = { 0.f,0.f,0.f };
		glm::vec3 m_size = { 1.f,1.f,0.f };
	};

	struct CircleBoundComp : public Component {
		glm::vec3 m_centerPt = { 0.f,0.f,0.f };
		BOG::fltPoint m_radius = 1.f;
	};

	struct ridgidBodyComp : public Component {
		BOG::fltPoint m_mass = 1.f;
		bool m_gravity = true;
		bool m_isKinematic = false;

		BOG::fltPoint m_speed = 0.f;
		glm::vec3 m_velocity = { 0.f,0.f,0.f };

	};

	struct Entity
	{
	//members
	public:
		std::string m_enName;
		std::array<Component*,6> m_enComponents;
		enTag tagId = enTag::NONE;
		bool isMesh = false;
	//constructor
	public:
		Entity(const char* name = "Entity") {
			m_enName = name;
			m_enComponents.fill(nullptr);
		}
		~Entity() {

		}

	//methods
	public:
		bool addComponent(Component* comp, BOG::compId id) {
			Component* component = m_enComponents[(uint16_t)id];

			if (!component) {
				m_enComponents[(uint16_t)id] = comp;
				return true;
			}
			return false;
		}
		bool removeComponent(BOG::compId id) {
			Component* component = m_enComponents[(uint16_t)id];

			if (!component) {
				m_enComponents[(uint16_t)id] = nullptr;
				return true;
			}
			return false;
		}

		Component* getComponent(BOG::compId id)
		{
			return m_enComponents[(uint16_t)id];
		}
	};

}



#endif //ENCMPSYS_H
