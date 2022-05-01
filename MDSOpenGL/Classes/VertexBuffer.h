#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

struct stVertex
{
	glm::vec3 m_v3Position;
	glm::vec3 m_v3Normal;
	glm::vec2 m_v2TextureUV;
	glm::vec3 m_v3Colour = glm::vec3(1, 1, 1);
};

class CVertexBuffer
{
private:
	GLuint m_GLuID;
	std::vector <stVertex> m_vVertices;

public:
	CVertexBuffer();
	CVertexBuffer(CVertexBuffer const&) = delete;
	CVertexBuffer(std::vector<stVertex>& _vVerticies);
	~CVertexBuffer();

	const GLuint& GetID();
	const std::vector<stVertex>& GetVertices() const;
	void SetVertices(std::vector<stVertex>& _vVertices);
	void Bind();
	void Unbind();
};