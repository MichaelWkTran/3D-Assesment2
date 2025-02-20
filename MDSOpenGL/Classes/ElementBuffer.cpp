#include "ElementBuffer.h"

CElementBuffer::CElementBuffer()
{
    glGenBuffers(1, &m_GLuID);
}

CElementBuffer::CElementBuffer(std::vector<GLuint>& _GLuIndicies)
{
    glGenBuffers(1, &m_GLuID);
    SetIndicies(_GLuIndicies);
}

CElementBuffer::~CElementBuffer()
{
    glDeleteBuffers(1, &m_GLuID);
}

const GLuint& CElementBuffer::GetID()
{
    return m_GLuID;
}

const std::vector<GLuint>& CElementBuffer::GetIndicies() const
{
    return m_vIndicies;
}

void CElementBuffer::SetIndicies(std::vector<GLuint>& _vIndicies)
{
    m_vIndicies = _vIndicies;

    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _vIndicies.size() * sizeof(GLuint), _vIndicies.data(), GL_STATIC_DRAW);
    Unbind();
}

void CElementBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_GLuID);
}

void CElementBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}