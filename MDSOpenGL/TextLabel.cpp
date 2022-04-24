#include "TextLabel.h"
#include "GlobalVariables.h"

GLuint CTextLabel::GenerateTexture(FT_Face _FontFace)
{
	GLuint GLuTextureID;
	glGenTextures(1, &GLuTextureID);
	glBindTexture(GL_TEXTURE_2D, GLuTextureID);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _FontFace->glyph->bitmap.width, _FontFace->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, _FontFace->glyph->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	return GLuTextureID;
}

CTextLabel::CTextLabel(std::string _strText, std::string _strFont, CShader* _pShader, glm::ivec2 _v2iPixelSize, glm::vec2 _v2Position, glm::vec2 _v2Scale/* = glm::vec2(1.0f, 1.0f)*/, glm::vec3 _v3Colour/* = glm::vec3(1.0f, 1.0f, 1.0f)*/)
{
	m_strText = _strText;
	m_pShader = _pShader;
	m_v2Position = _v2Position;
	m_v2Scale = _v2Scale;
	m_v3Colour = _v3Colour;
	m_mat4Projection = glm::ortho(0.0f, (GLfloat)uViewPortW, 0.0f, (GLfloat)uViewPortH, 0.0f, 100.0f);
	
	FT_Library FontLibrary;
	FT_Face FontFace;

	//Initializing the Library object
	if (FT_Init_FreeType(&FontLibrary) != 0)
	{
		std::cout << "FreeType Error: Could not init FreeType Library";
		return;
	}
	//Loading the font as face
	if (FT_New_Face(FontLibrary, _strFont.c_str(), 0, &FontFace) != 0)
	{
		std::cout << "FreeType Error: Failed to load font";
		return;
	}

	FT_Set_Pixel_Sizes(FontFace, _v2iPixelSize.x, _v2iPixelSize.y);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Load the characters of the font up to the font character limit
	for (GLubyte Glyph = 0; Glyph < m_iFontCharacterLimit; Glyph++)
	{
		//Load the character glyph into face
		if (FT_Load_Char(FontFace, Glyph, FT_LOAD_RENDER))
		{
			std::cout << "FreeType Error: Failed to load Glyph: " << (unsigned char)Glyph << std::endl;
			continue;
		}

		stFontChar FontCharacter =
		{
			GenerateTexture(FontFace),
			glm::ivec2(FontFace->glyph->bitmap.width,
			FontFace->glyph->bitmap.rows),
			glm::ivec2(FontFace->glyph->bitmap_left,
			FontFace->glyph->bitmap_top),
			(GLuint)FontFace->glyph->advance.x / 64
		};
		
		m_mapCharacter.insert(std::pair<GLchar, stFontChar>(Glyph, FontCharacter));
	}

	//Destroy FontLibrary and FontFace
	FT_Done_Face(FontFace);
	FT_Done_FreeType(FontLibrary);

	//Configure the VAO and VBO for texture quads
	glGenBuffers(1, &VBODynamicQuad);

	m_VertexArray.Bind(); glBindBuffer(GL_ARRAY_BUFFER, VBODynamicQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	
	m_VertexArray.LinkAttribute(0 /**/, 4, GL_FLOAT, 4 * sizeof(GLfloat), (void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); m_VertexArray.Unbind();
}

CTextLabel::~CTextLabel()
{
}

void CTextLabel::Render()
{
	if (!m_bInitialized || m_pShader == nullptr) return;

	//Enable Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Bind VAO and Shader
	m_pShader->Activate(); m_VertexArray.Bind();

	glUniform3fv(glGetUniformLocation(m_pShader->GetID(), "TextColor"), 1, glm::value_ptr(m_v3Colour));
	glUniformMatrix4fv(glGetUniformLocation(m_pShader->GetID(), "ProjectionMat"), 1, GL_FALSE, glm::value_ptr(m_mat4Projection));

	// Store Character Origin that can change as we write each character. Keep the starting text position intact.
	glm::vec2 v2CharacterOrigin = m_v2Position; 
	
	// Iterate through the text characters
	for (std::string::const_iterator TextCharacter = m_strText.begin(); TextCharacter != m_strText.end(); TextCharacter++)
	{
		stFontChar FontCharacter = m_mapCharacter[*TextCharacter];
		
		GLfloat GLfPosX = v2CharacterOrigin.x + FontCharacter.v2iBearing.x * m_v2Scale.x;
		GLfloat GLfPosY = v2CharacterOrigin.y - (FontCharacter.v2iSize.y - FontCharacter.v2iBearing.y) * m_v2Scale.y;
		
		GLfloat GLfWidth = FontCharacter.v2iSize.x * m_v2Scale.x;
		GLfloat GLfHeight = FontCharacter.v2iSize.y * m_v2Scale.y;

		// Update VB0 for each character
		GLfloat GLsvertices[6][4] =
		{
			{ GLfPosX, GLfPosY + GLfHeight, 0.0, 0.0 }, { GLfPosX, GLfPosY, 0.0, 1.0 }, { GLfPosX + GLfWidth, GLfPosY, 1.0, 1.0 }, { GLfPosX, GLfPosY + GLfHeight, 0.0, 0.0 },
			{ GLfPosX + GLfWidth, GLfPosY, 1.0, 1.0 },{ GLfPosX + GLfWidth, GLfPosY + GLfHeight, 1.0, 0.0 },
		};

		// Reload the vertex array to the VB0
		glBindBuffer(GL_ARRAY_BUFFER, VBODynamicQuad);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLsvertices), GLsvertices);

		// Render the glyph texture over the quad
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, FontCharacter.GLuTextureID);
		glUniform1i(glGetUniformLocation(m_pShader->GetID(), "TextTexture"), 0);
		glDrawArrays(GL_TRIANGLES, 0, 6); 
		
		// Move the position of the origin point for the next glyph by the advance
		v2CharacterOrigin.x += FontCharacter.GLuAdvance * m_v2Scale.x;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); m_VertexArray.Unbind(); glBindTexture(GL_TEXTURE_2D, 0); glDisable(GL_BLEND);
}