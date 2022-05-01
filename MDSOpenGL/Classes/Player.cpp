#include "Player.h"
#include "../ExternVariables.h"

CPlayer::CPlayer()
{
    const float fMeshSize = 0.15f;
    std::vector<stVertex> vVertices =
    {
        //Coordinates                                      Normals                       Texture Cordinate
        stVertex{glm::vec3(-0.5f, 0.5f, 0.5f) * fMeshSize, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f,1.0f)}, //Front
        stVertex{glm::vec3(-0.5f,-0.5f, 0.5f) * fMeshSize, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f,0.0f)},
        stVertex{glm::vec3(0.5f,-0.5f, 0.5f) * fMeshSize, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f,0.0f)},
        stVertex{glm::vec3(0.5f, 0.5f, 0.5f) * fMeshSize, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f,1.0f)},

        stVertex{glm::vec3(0.5f, 0.5f,-0.5f) * fMeshSize, glm::vec3(0.0f,-1.0f, 0.0f), glm::vec2(0.0f,1.0f)}, //Back
        stVertex{glm::vec3(0.5f,-0.5f,-0.5f) * fMeshSize, glm::vec3(0.0f,-1.0f, 0.0f), glm::vec2(0.0f,0.0f)},
        stVertex{glm::vec3(-0.5f,-0.5f,-0.5f) * fMeshSize, glm::vec3(0.0f,-1.0f, 0.0f), glm::vec2(1.0f,0.0f)},
        stVertex{glm::vec3(-0.5f, 0.5f,-0.5f) * fMeshSize, glm::vec3(0.0f,-1.0f, 0.0f), glm::vec2(1.0f,1.0f)},

        stVertex{glm::vec3(0.5f, 0.5f, 0.5f) * fMeshSize, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f,1.0f)}, //Right
        stVertex{glm::vec3(0.5f,-0.5f, 0.5f) * fMeshSize, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f,0.0f)},
        stVertex{glm::vec3(0.5f,-0.5f,-0.5f) * fMeshSize, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f,0.0f)},
        stVertex{glm::vec3(0.5f, 0.5f,-0.5f) * fMeshSize, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f,1.0f)},

        stVertex{glm::vec3(-0.5f, 0.5f,-0.5f) * fMeshSize, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f,1.0f)}, //Left
        stVertex{glm::vec3(-0.5f,-0.5f,-0.5f) * fMeshSize, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f,0.0f)},
        stVertex{glm::vec3(-0.5f,-0.5f, 0.5f) * fMeshSize, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f,0.0f)},
        stVertex{glm::vec3(-0.5f, 0.5f, 0.5f) * fMeshSize, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f,1.0f)},

        stVertex{glm::vec3(-0.5f, 0.5f,-0.5f) * fMeshSize, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f,1.0f)}, //Front
        stVertex{glm::vec3(-0.5f, 0.5f, 0.5f) * fMeshSize, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f,0.0f)},
        stVertex{glm::vec3(0.5f, 0.5f, 0.5f) * fMeshSize, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f,0.0f)},
        stVertex{glm::vec3(0.5f, 0.5f,-0.5f) * fMeshSize, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f,1.0f)},

        stVertex{glm::vec3(-0.5f,-0.5f, 0.5f) * fMeshSize, glm::vec3(0.0f, 0.0f,-1.0f), glm::vec2(0.0f,1.0f)}, //Bottom
        stVertex{glm::vec3(-0.5f,-0.5f,-0.5f) * fMeshSize, glm::vec3(0.0f, 0.0f,-1.0f), glm::vec2(0.0f,0.0f)},
        stVertex{glm::vec3(0.5f,-0.5f,-0.5f) * fMeshSize, glm::vec3(0.0f, 0.0f,-1.0f), glm::vec2(1.0f,0.0f)},
        stVertex{glm::vec3(0.5f,-0.5f, 0.5f) * fMeshSize, glm::vec3(0.0f, 0.0f,-1.0f), glm::vec2(1.0f,1.0f)}
    };

    std::vector<GLuint> vIndices =
    {
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 13, 14,
        12, 14, 15,
        16, 17, 18,
        16, 18, 19,
        20, 21, 22,
        20, 22, 23
    };

    m_Mesh.SetVerticies(vVertices); m_Mesh.SetIndicies(vIndices); 
    m_Mesh.m_vTextures.push_back(CTextureManager::Insert("Resources/Textures/Planks.png", "Diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE));
    m_Mesh.m_vTextures.push_back(CTextureManager::Insert("Resources/Textures/PlanksSpecular.png", "Specular", 1, GL_RED, GL_UNSIGNED_BYTE));
    
    m_bUpdateTransform = false;
    m_mat4Model = glm::mat4x4(1);
    m_v3Position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_fquatRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    m_v3Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

const CShader* CPlayer::GetShader() const { return m_Mesh.m_pShader; }   /**/ void CPlayer::SetShader(CShader* _Shader) { m_Mesh.m_pShader = _Shader; };
const glm::vec3& CPlayer::GetPosition() const { return m_v3Position; }    /**/ void CPlayer::SetPosition(const glm::vec3 _v3Position) { m_v3Position = _v3Position; m_bUpdateTransform = true; }
const glm::quat& CPlayer::GetRotation() const { return m_fquatRotation; } /**/ void CPlayer::SetRotation(const glm::quat _fquatRotation) { m_fquatRotation = _fquatRotation; m_bUpdateTransform = true; }
const glm::vec3& CPlayer::GetScale() const { return m_v3Scale; }          /**/ void CPlayer::SetScale(const glm::vec3 _v3Scale) { m_v3Scale = _v3Scale; m_bUpdateTransform = true; }

void CPlayer::Input(GLFWwindow* _pWindow)
{
    glm::vec3 v3MovementInput
    (
        (glfwGetKey(_pWindow, GLFW_KEY_A) == GLFW_PRESS) - (glfwGetKey(_pWindow, GLFW_KEY_D) == GLFW_PRESS),
        (glfwGetKey(_pWindow, GLFW_KEY_Q) == GLFW_PRESS) - (glfwGetKey(_pWindow, GLFW_KEY_E) == GLFW_PRESS),
        (glfwGetKey(_pWindow, GLFW_KEY_W) == GLFW_PRESS) - (glfwGetKey(_pWindow, GLFW_KEY_S) == GLFW_PRESS)
    );
    if (v3MovementInput == glm::vec3()) return void();

    SetPosition(GetPosition() + (v3MovementInput * fDeltatime));
}

void CPlayer::Draw(CCamera& _Camera)
{
    if (m_Mesh.m_pShader == nullptr) return void();

    if (m_bUpdateTransform)
    {
        m_mat4Model = glm::mat4x4(1);
        m_mat4Model = glm::scale(m_mat4Model, m_v3Scale) * glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), m_fquatRotation * glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m_mat4Model = glm::translate(m_mat4Model, m_v3Position);
        m_bUpdateTransform = false;
    }
    
    m_Mesh.m_pShader->Activate();
    glUniformMatrix4fv(glGetUniformLocation(m_Mesh.m_pShader->GetID(), "uni_mat4Model"), 1, GL_FALSE, glm::value_ptr(m_mat4Model));
    m_Mesh.Draw(_Camera);
}