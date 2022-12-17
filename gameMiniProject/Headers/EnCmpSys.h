#ifndef ENCMPSYS_H
#define ENCMPSYS_H

#include "Mesh.h"
#include "Transform.h"

namespace BOG {

	enum class enTag :uint16_t {
		NONE = 0,PLAYER,TILE
	};

	enum class compId :uint16_t {
		NONE = 0, TRANFORM, MATERIAL, MESH
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

	struct Entity
	{
	//members
	public:
		std::string m_enName;
		std::vector<Component*> m_enComponents;
		enTag tagId = enTag::NONE;
		bool isMesh = false;
	//constructor
	public:
		Entity(const char* name = "Entity") {
			m_enName = name;
		}
		~Entity() {

		}

	//methods
	public:
		void addComponent(Component* comp, BOG::compId id) {
			std::vector<Component*>::iterator keyVal = std::find_if(m_enComponents.begin(), m_enComponents.end(), [&](Component* iteComp) {
					return comp->m_compId == iteComp->m_compId;
				});

			if (keyVal == m_enComponents.end())
			{
				comp->m_compId = (uint16_t)id;
				m_enComponents.push_back(comp);
			}
		}
		void removeComponent(BOG::compId id) {
			std::vector<Component*>::iterator keyVal = std::find_if(m_enComponents.begin(), m_enComponents.end(), [&](Component* iteComp) {
				return (uint16_t)id == iteComp->m_compId;
				});

			if (keyVal != m_enComponents.end())
				m_enComponents.erase(keyVal);
		}

		Component* getComponent(uint16_t id)
		{
			return m_enComponents[id];
		}
	};

}



#endif //ENCMPSYS_H
