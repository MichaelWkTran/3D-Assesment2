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
	
	CMesh() { m_pShader = nullptr; m_bUpdateVertexArray = true; };
	bool m_bUpdateVertexArray;
	virtual void UpdateVertexArray();

public:
	std::vector <CTexture> m_vTextures;
	CShader* m_pShader;

	CMesh(std::vector<stVertex>& _vVerticies, std::vector<GLuint>& _vIndicies, std::vector <CTexture>& _Textures, CShader& _Shader);

	std::vector <stVertex> GetVerticies() const;
	void SetVerticies(std::vector<stVertex>& _vVerticies);
	std::vector <GLuint> GetIndicies() const;
	void SetIndicies(std::vector<GLuint>& _vIndicies);

	void Draw(CCamera& _Camera);
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