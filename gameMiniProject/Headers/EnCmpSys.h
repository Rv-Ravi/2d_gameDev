#ifndef ENCMPSYS_H
#define ENCMPSYS_H

#include "Mesh.h"
#include "Transform.h"

namespace BOG {

	enum class enTag :uint16_t {
		NONE = 0,PLAYER,TILE
	};

	enum class compId :uint16_t {
		MESH = 0,TRANSFORM,MATERIAL,BOUNDNGBOX
	};

	enum class boundngType : uint16_t {
		NONE = 0, BOX,CIRCLE,LINE
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

	struct BoundngBoxComp : public Component {
		bool m_collision = true;
		BOG::boundngType m_bType = BOG::boundngType::BOX;

		glm::vec4 m_boundLimit = { -1.f,-1.f,1.f,1.f };

		//methods
		void setBoundngBox(const glm::vec4& boundngBox) {
			if (m_bType == BOG::boundngType::BOX) {
				m_boundLimit = boundngBox;
			}
			else if (m_bType == BOG::boundngType::CIRCLE || m_bType == BOG::boundngType::LINE) {
				m_boundLimit.x = boundngBox.x;
				m_boundLimit.y = boundngBox.y;
				m_boundLimit.z = 0.f, m_boundLimit.w = 0.f;
			}
		}
	};

	struct Entity
	{
	//members
	public:
		std::string m_enName;
		std::array<Component*,4> m_enComponents;
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
		void addComponent(Component* comp, BOG::compId id) {
			Component* component = m_enComponents[(uint16_t)id];

			if (!component) {
				m_enComponents[(uint16_t)id] = comp;

				if (id == BOG::compId::BOUNDNGBOX) {
					setBoundngBox();
				}
			}
		}
		void removeComponent(BOG::compId id) {
			Component* component = m_enComponents[(uint16_t)id];

			if (!component) {
				m_enComponents[(uint16_t)id] = nullptr;
			}
		}

		Component* getComponent(BOG::compId id)
		{
			return m_enComponents[(uint16_t)id];
		}

	private:
		void setBoundngBox() {
			BoundngBoxComp* bBox = (BoundngBoxComp*)m_enComponents[(uint16_t)BOG::compId::BOUNDNGBOX];
			TransformComp* tComp = (TransformComp*)m_enComponents[(uint16_t)BOG::compId::TRANSFORM];
			Transform trans;
			if (tComp && bBox)
			{
				glm::mat4 tranMat = trans.getModelMat(tComp->m_position, tComp->m_rotation, tComp->m_scale);
				glm::vec4 limit1(bBox->m_boundLimit.x, bBox->m_boundLimit.y,0.f,1.f);
				glm::vec4 limit2(bBox->m_boundLimit.z, bBox->m_boundLimit.w, 0.f, 1.f);

				limit1 = tranMat * limit1;
				limit2 = tranMat * limit2;

				bBox->setBoundngBox(glm::vec4(limit1.x,limit1.y, limit2.x,limit2.y));
			}
		}
	};

}



#endif //ENCMPSYS_H
