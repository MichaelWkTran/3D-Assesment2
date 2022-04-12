#pragma once

#include <glm/glm.hpp>
#include <GLEW/glew.h>
#include <vector>

struct stVertex
{
	glm::vec3 m_v3Position;
	glm::vec3 m_v3Normal;
	glm::vec2 m_v3TextureUV;
	glm::vec3 m_v3Colour = glm::vec3(1, 1, 1);
};

struct stTriangle
{
	GLuint m_Indicies[3];
	glm::vec3 m_v3Normals[3];
	glm::vec2 m_v3TextureUV[3];
	glm::vec3 m_v3Colours[3] = {glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1)};
};

class CVertexBuffer
{
private:
	GLuint m_GLuID;

public:
	CVertexBuffer(std::vector<stVertex>& _vVerticies);
	~CVertexBuffer();

	const GLuint GetID();
	void Bind();
	void Unbind();
};