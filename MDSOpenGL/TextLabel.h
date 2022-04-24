#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <FREETYPE/ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>
#include <iostream>

#include "Classes/Shader.h"
#include "Classes/VertexArray.h"
#include "Classes/VertexBuffer.h"

class CTextLabel
{
private:
	struct stFontChar
	{
		GLuint GLuTextureID = 0;
		glm::ivec2 v2iSize;
		glm::ivec2 v2iBearing;
		GLuint GLuAdvance = 0;
	};

	static const int m_iFontCharacterLimit = 128;
	bool m_bInitialized = false;
	glm::mat4 m_mat4Projection;
	std::map<GLchar, stFontChar> m_mapCharacter;

	CVertexArray m_VertexArray;
	GLuint VBODynamicQuad;

	GLuint GenerateTexture(FT_Face _Face);

public:
	std::string m_strText;
	glm::vec2 m_v2Position;
	glm::vec2 m_v2Scale;
	glm::vec3 m_v3Colour;
	CShader* m_pShader;

	CTextLabel
	(
		std::string _strText,
		std::string _strFont,
		CShader* _pShader,
		glm::ivec2 _v2iPixelSize,
		glm::vec2 _v2Position,
		glm::vec2 _v2Scale = glm::vec2(1.0f, 1.0f),
		glm::vec3 _v3Colour = glm::vec3(1.0f, 1.0f, 1.0f)
	);
	~CTextLabel();

	void Render();
};