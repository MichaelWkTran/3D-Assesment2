#include "VertexArray.h"

CVertexArray::CVertexArray()
{
    glGenVertexArrays(1, &m_GLuID);
}

CVertexArray::~CVertexArray()
{
    glDeleteVertexArrays(1, &m_GLuID);
}

const GLuint& CVertexArray::GetID()
{
    return m_GLuID;
}

void CVertexArray::LinkAttribute
(
    GLuint GluLayout,
    GLuint _GLuNumComponents,
    GLenum _GLeType,
    GLsizeiptr _Stride,
    void* _Offset
)
{
    glVertexAttribPointer(GluLayout, _GLuNumComponents, _GLeType, GL_FALSE, _Stride, _Offset);
    glEnableVertexAttribArray(GluLayout);
}

void CVertexArray::Bind()
{
    glBindVertexArray(m_GLuID);
}

void CVertexArray::Unbind()
{
    glBindVertexArray(0);
}