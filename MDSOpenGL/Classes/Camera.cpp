#include "Camera.h"

CCamera::CCamera
(
	unsigned int* _pViewPortW,
	unsigned int* _pViewPortH,
	bool _IsPerspective,
	glm::vec3 _v3Position/* = glm::vec3(0.0f, 0.0f, 0.0f)*/,
	glm::vec3 _v3Orientation/* = glm::vec3(0.0f, 0.0f, 1.0f)*/,
	float _fFOVorScale/* = 0.0f*/,
	float _fNearPlane/* = 0.1f*/, float _fFarPlane/* = 100.0f*/
)
{
	m_pViewPortW = _pViewPortW;
	m_pViewPortH = _pViewPortH;

	m_IsPerspective = _IsPerspective;
	m_v3Position = _v3Position;
	m_v3Orientation = _v3Orientation;
	if (_fFOVorScale == 0.0f)
	{
		m_fFOV = 45.0f; m_fOrthographicScale = 1;
	}
	else
	{
		m_fFOV = 45.0f; m_fOrthographicScale = 1;

		if (_IsPerspective) { m_fFOV = _fFOVorScale; }
		else { m_fOrthographicScale = _fFOVorScale; }
	}
	m_fNearPlane = _fNearPlane;
	m_fFarPlane = _fFarPlane;

	m_mat4View = glm::mat4(1.0f);
	m_mat4Projection = glm::mat4(1.0f);
	m_mat4Camera = glm::mat4(1.0f);

	UpdateProjectionMatrix();
	Update();
}

void CCamera::UpdateProjectionMatrix()
{
	if (m_IsPerspective)
	{
		m_mat4Projection = glm::perspective(glm::radians(m_fFOV), ((float)(*m_pViewPortW)) / ((float)(*m_pViewPortH)), m_fNearPlane, m_fFarPlane);
	}
	else
	{
		float fHalfViewPortW = (((float)(*m_pViewPortW)) / 2) / m_fOrthographicScale;
		float fHalfViewPortH = (((float)(*m_pViewPortH)) / 2) / m_fOrthographicScale;

		m_mat4Projection = glm::ortho(fHalfViewPortW, -fHalfViewPortW, fHalfViewPortH, -fHalfViewPortH, m_fNearPlane, m_fFarPlane);
	}
}

const glm::mat4& CCamera::GetViewMatrix()
{
	return m_mat4View;
}

const glm::mat4& CCamera::GetProjectionMatrix()
{
	return m_mat4Projection;
}

const glm::mat4& CCamera::GetCameraMatrix()
{
	return m_mat4Camera;
}

const float CCamera::GetFOV(bool _InRadians/* = false*/)
{
	if (_InRadians) return glm::radians(m_fFOV);
	else return m_fFOV;
}

void CCamera::SetFOV(float _FOV, bool _IsRadians/* = false*/)
{
	m_fFOV = _IsRadians ? glm::degrees(_FOV) : _FOV;

	UpdateProjectionMatrix();
}

const float& CCamera::GetNearPlane()
{
	return m_fNearPlane;
}

void CCamera::SetNearPlane(float _fNearPlane)
{
	m_fNearPlane = _fNearPlane;

	UpdateProjectionMatrix();
}

const float& CCamera::GetFarPlane()
{
	return m_fFarPlane;
}

void CCamera::SetFarPlane(float _fFarPlane)
{
	m_fFarPlane = _fFarPlane;

	UpdateProjectionMatrix();
}

void CCamera::Update()
{
	m_mat4View = glm::lookAt(m_v3Position, m_v3Position + m_v3Orientation, glm::vec3(0.0f, 1.0f, 0.0f));
	m_mat4Camera = m_mat4Projection * m_mat4View;
}