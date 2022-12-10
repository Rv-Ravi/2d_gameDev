#include "../Headers/Mesh.h"



BOG::Mesh::Mesh()
{
	ErrCheck(glGenVertexArrays(1, &m_VAO));
	ErrCheck(glGenBuffers(1, &m_VBO));
	ErrCheck(glGenBuffers(1, &m_IBO));
}

BOG::Mesh::Mesh(const std::vector<BOG::vertexData>& objData,const std::vector<uint32_t>& objIndex)
	:m_objDataLen(objData.size()),m_objIndexLen(objIndex.size())
{
	ErrCheck(glGenVertexArrays(1, &m_VAO));
	ErrCheck(glGenBuffers(1, &m_VBO));
	ErrCheck(glGenBuffers(1, &m_IBO));

	setBufferData(objData,objIndex);
}

BOG::Mesh::~Mesh()
{
	clearBuffer();
}

BOG::Mesh::Mesh(const Mesh& mesh)
{
	m_objDataLen = mesh.m_objDataLen;
	m_objIndexLen = mesh.m_objIndexLen;
	m_VAO = mesh.m_VAO;
	m_VBO = mesh.m_VBO;
	m_IBO = mesh.m_IBO;
}

BOG::Mesh::Mesh(Mesh&& mesh)
{
	m_objDataLen = mesh.m_objDataLen;
	m_objIndexLen = mesh.m_objIndexLen;
	m_VAO = mesh.m_VAO;
	m_VBO = mesh.m_VBO;
	m_IBO = mesh.m_IBO;
}

BOG::Mesh& BOG::Mesh::operator=(const BOG::Mesh& mesh)
{
	if (this != &mesh)
	{
		m_objDataLen = mesh.m_objDataLen;
		m_objIndexLen = mesh.m_objIndexLen;
		m_VAO = mesh.m_VAO;
		m_VBO = mesh.m_VBO;
		m_IBO = mesh.m_IBO;
	}
	return *this;
}

BOG::Mesh& BOG::Mesh::operator=(BOG::Mesh&& mesh)
{
	if (this != &mesh)
	{
		m_objDataLen = mesh.m_objDataLen;
		m_objIndexLen = mesh.m_objIndexLen;
		m_VAO = mesh.m_VAO;
		m_VBO = mesh.m_VBO;
		m_IBO = mesh.m_IBO;
	}
	return *this;
}

void BOG::Mesh::setBufferData(const std::vector<BOG::vertexData>& objData, const std::vector<uint32_t>& objIndex)
{


	ErrCheck(glBindVertexArray(m_VAO));
	ErrCheck(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
	ErrCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));

	ErrCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(BOG::vertexData) * m_objDataLen, &objData[0], GL_STATIC_DRAW));
	ErrCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_objIndexLen, &objIndex[0], GL_STATIC_DRAW));

	ErrCheck(glEnableVertexAttribArray(0));
	ErrCheck(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BOG::vertexData), &((BOG::vertexData*)0)->vertexPos));
	ErrCheck(glEnableVertexAttribArray(1));
	ErrCheck(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BOG::vertexData), &((BOG::vertexData*)0)->vertexCol));
	ErrCheck(glEnableVertexAttribArray(2));
	ErrCheck(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BOG::vertexData), &((BOG::vertexData*)0)->texCoord));
	ErrCheck(glEnableVertexAttribArray(3));
	ErrCheck(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(BOG::vertexData), &((BOG::vertexData*)0)->vertexNormal));


	ErrCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
	ErrCheck(glBindVertexArray(0));
	ErrCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void BOG::Mesh::addObject(const std::vector<BOG::vertexData>& objData, const std::vector<uint32_t>& objIndex)
{
	m_objDataLen = objData.size();
	m_objIndexLen = objIndex.size();
	setBufferData(objData, objIndex);
}

void BOG::Mesh::clearBuffer()
{
	if (m_VAO != 0)
	{
		glDeleteBuffers(1, &m_VAO); m_VAO = 0;
	}
	if (m_VBO != 0)
	{
		glDeleteBuffers(1, &m_VBO); m_VBO = 0;
	}
	if (m_IBO != 0)
	{
		glDeleteBuffers(1, &m_IBO); m_IBO = 0;
	}
}

void BOG::Mesh::meshBind()
{
	glBindVertexArray(m_VAO);
}

void BOG::Mesh::meshUnbind()
{
	glBindVertexArray(0);
}
