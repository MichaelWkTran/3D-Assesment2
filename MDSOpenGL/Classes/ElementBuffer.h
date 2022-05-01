#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class CElementBuffer
{
private:
	GLuint m_GLuID;
	std::vector<GLuint> m_vIndicies;

public:
	CElementBuffer();
	CElementBuffer(CElementBuffer const&) = delete;
	CElementBuffer(std::vector<GLuint>& _GLuIndicies);
	~CElementBuffer();

	const GLuint& GetID();
	const std::vector<GLuint>& GetIndicies() const;
	void SetIndicies(std::vector<GLuint>& _vIndicies);
	void Bind();
	void Unbind();
};

