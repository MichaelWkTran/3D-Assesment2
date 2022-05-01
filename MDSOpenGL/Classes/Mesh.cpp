#include "Mesh.h"

void CMesh::UpdateVertexArray()
{
	if (!m_bUpdateVertexArray || m_pShader == nullptr) return void();
	m_bUpdateVertexArray = false;

	m_VertexArray.Bind(); m_VertexBuffer.Bind(); m_ElementBuffer.Bind();

	m_VertexArray.LinkAttribute(0 /*m_v3CurrentPosition*/, 3, GL_FLOAT, sizeof(stVertex), (void*)0);
	m_VertexArray.LinkAttribute(1 /*m_v3Normal*/, 3, GL_FLOAT, sizeof(stVertex), (void*)(3 * sizeof(float)));
	m_VertexArray.LinkAttribute(2 /*m_v2TextureCoord*/, 2, GL_FLOAT, sizeof(stVertex), (void*)(6 * sizeof(float)));
	m_VertexArray.LinkAttribute(3 /*m_v3Color*/, 3, GL_FLOAT, sizeof(stVertex), (void*)(8 * sizeof(float)));

	m_VertexArray.Unbind(); m_VertexBuffer.Unbind(); m_ElementBuffer.Unbind();
}

CMesh::CMesh()
{
	m_pShader = nullptr;
	m_bUpdateVertexArray = false;
};

CMesh::CMesh(std::vector<stVertex>& _vVerticies, std::vector<GLuint>& _vIndicies, std::vector<CTexture*>& _vTextures, CShader* _Shader)
{
	m_VertexBuffer.SetVertices(_vVerticies);
	m_ElementBuffer.SetIndicies(_vIndicies);
	m_vTextures = _vTextures;
	m_pShader = _Shader;

	m_bUpdateVertexArray = true;
}

const std::vector<stVertex>& CMesh::GetVerticies() const
{
	return m_VertexBuffer.GetVertices();
}

void CMesh::SetVerticies(std::vector<stVertex>& _vVerticies)
{
	m_VertexBuffer.SetVertices(_vVerticies);
	m_bUpdateVertexArray = true;
}

const std::vector<GLuint>& CMesh::GetIndicies() const
{
	return m_ElementBuffer.GetIndicies();
}

void CMesh::SetIndicies(std::vector<GLuint>& _vIndicies)
{
	m_ElementBuffer.SetIndicies(_vIndicies);
	m_bUpdateVertexArray = true;
}

void CMesh::Draw(CCamera& _Camera)
{
	if (m_pShader == nullptr || m_VertexBuffer.GetVertices().empty()) return void();

	UpdateVertexArray();

	m_pShader->Activate();
	m_VertexArray.Bind();

	unsigned int uNumDiffuse = 0;
	unsigned int uNumSpecular = 0;
	for (unsigned int i = 0; i < m_vTextures.size(); i++)
	{
		std::string strNum;
		std::string strType = m_vTextures[i]->m_pType;

		if (strType == "Diffuse") { strNum = std::to_string(uNumDiffuse++); }
		else if (strType == "Specular") { strNum = std::to_string(uNumSpecular++); }
		else { continue; }

		m_vTextures[i]->Bind();
		glUniform1i(glGetUniformLocation(m_pShader->GetID(), ("uni_samp2D" + strType + '[' + strNum + ']').c_str()), m_vTextures[i]->m_GLuUnit);

		if (i >= m_vTextures.size() - 1) CTextureManager::Unbind();
	}

	glUniform3f(glGetUniformLocation(m_pShader->GetID(), "uni_v3CameraPosition"), _Camera.m_v3Position.x, _Camera.m_v3Position.y, _Camera.m_v3Position.z);
	glUniformMatrix4fv(glGetUniformLocation(m_pShader->GetID(), "uni_mat4CameraMatrix"), 1, GL_FALSE, glm::value_ptr(_Camera.GetCameraMatrix()));

	glDrawElements(GL_TRIANGLES, m_ElementBuffer.GetIndicies().size(), GL_UNSIGNED_INT, 0);
	m_VertexArray.Unbind();
}