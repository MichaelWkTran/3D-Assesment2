#include "VertexBuffer.h"

CVertexBuffer::CVertexBuffer(std::vector<stVertex>& _vVerticies)
{
    glGenBuffers(1, &m_GLuID);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, _vVerticies.size() * sizeof(stVertex), _vVerticies.data(), GL_STATIC_DRAW);
    Unbind();

    _vVerticies = std::vector<stVertex>();
}

CVertexBuffer::~CVertexBuffer()
{
    glDeleteBuffers(1, &m_GLuID);
}

const GLuint CVertexBuffer::GetID()
{
    return m_GLuID;
}

void CVertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_GLuID);
}

void CVertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}