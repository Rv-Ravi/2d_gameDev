#ifndef MESH_H
#define MESH_H

#include "appInitialize.h"

namespace BOG {
	class Mesh
	{
	//Members
	private:
		uint32_t m_objDataLen = 0, m_objIndexLen = 0, m_VAO = 0, m_VBO = 0, m_IBO = 0;
	//constructors
	public:
		Mesh();
		Mesh(const std::vector<BOG::vertexData>& objData,const std::vector<uint32_t>& objIndex);
		~Mesh();

		Mesh(const Mesh& mesh);
		Mesh(Mesh&& mesh);

	//operators
	public:
		Mesh& operator=(const Mesh& mesh);
		Mesh& operator=(Mesh&& mesh);

	//getter and setter
	public:
		inline int32_t getVaoId() const { return m_VAO; }
		inline int32_t getVboId() const { return m_VBO; }
		inline int32_t getIboId() const { return m_IBO; }
		inline uint32_t getObjDataLen() const { return m_objDataLen; }
		inline uint32_t getObjIndexLen() const { return m_objIndexLen; }

	//methods
	private:
		void setBufferData(const std::vector<BOG::vertexData>& objData, const std::vector<uint32_t>& objIndex);

	public:
		void addObject(const std::vector<BOG::vertexData>& objData, const std::vector<uint32_t>& objIndex);
		void clearBuffer();
		void meshBind();
		static void meshUnbind();
	};

}

#endif //MESH_H
