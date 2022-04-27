#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <map>
#include <iostream>

class CTexture;

class CTextureManager
{
private:
	static std::map<GLuint /*Texture ID*/, CTexture*> mapTextures;

public:
	static bool Empty();
	static unsigned int Size();
	static unsigned int MaxSize();

	CTexture* operator[](unsigned int _GLuID);
	static CTexture* At(unsigned int _GLuID);

	static CTexture* Insert(const char* _pType, GLuint&& _GLuSlot, const char* _pName = "");
	static CTexture* Insert(const char* _pImage, const char* _pType, GLuint&& _GLuSlot, GLenum&& _GLeFormat, GLenum&& _GLePixelType, const char* _pName = "");
	static void Erase(unsigned int _GLuID);
	static void Clear();

	static void Bind(unsigned int _GLuID);
	static void Unbind();
};

class CTexture
{
private:
	friend CTextureManager;

	GLuint m_GLuID;

	CTexture(const char* _pName, const char* _pType, GLuint&& _GLuSlot);
	CTexture(CTexture const&) = delete;
	~CTexture();

public:
	const char* m_pName;
	const char* m_pType;
	GLuint m_GLuUnit;
	
	const GLuint GetID() const;
	void Bind() const;
	static void Unbind();
};