#pragma once

#include <glm/glm.hpp>
#include <GLEW/glew.h>
#include <vector>

class CElementBuffer
{
private:
	GLuint m_GLuID;
	
public:
	CElementBuffer(std::vector<GLuint>& _GLuIndicies);
	~CElementBuffer();

	const GLuint GetID();
	void Bind();
	void Unbind();
};

