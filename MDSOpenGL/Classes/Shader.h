#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

class CShader
{
public:
	static std::string GetFileContents(const char* _pFileName);

	CShader(const char* _pVertexFile, const char* _pFragmentFile, const char* _pGeometryFile = "");
	~CShader();

	GLuint GetID();
	void Activate();
	void Deactivate();

private:
	GLuint m_GLuID;
	bool m_UsesGeometryShader;

	void CompileErrors(unsigned int _uShader, const char* _pType);
};