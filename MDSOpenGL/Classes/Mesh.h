#pragma once

#include <string>
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Camera.h"
#include "Texture.h"

class CMesh
{
protected:
	CVertexArray m_VertexArray;
	std::vector <stVertex> m_vVerticies;
	std::vector <GLuint> m_vIndicies;
	
	bool m_bUpdateVertexArray;
	virtual void UpdateVertexArray();

public:
	std::vector <CTexture> m_vTextures;
	CShader* m_pShader;

	CMesh();
	CMesh(std::vector<stVertex>& _vVerticies, std::vector<GLuint>& _vIndicies, std::vector <CTexture>& _Textures, CShader& _Shader);

	std::vector <stVertex> GetVerticies() const;
	void SetVerticies(std::vector<stVertex>& _vVerticies);
	std::vector <GLuint> GetIndicies() const;
	void SetIndicies(std::vector<GLuint>& _vIndicies);

	void Draw(CCamera& _Camera);
};

struct stTriangle
{
	GLuint m_Indicies[3];
	glm::vec3 m_v3Normals[3];
	glm::vec2 m_v3TextureUV[3];
	glm::vec3 m_v3Colours[3] = { glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1) };
};

class CMeshTris : public CMesh
{
protected:
	std::vector <glm::vec3> m_vVertexPositions;
	std::vector <stTriangle> m_vTriangles;

	virtual void UpdateVertexArray();

public:
	CMeshTris(std::vector<glm::vec3>& _vVertexPositions, std::vector<stTriangle>& _vTriangles, std::vector <CTexture>& _vTextures, CShader& _Shader);
};