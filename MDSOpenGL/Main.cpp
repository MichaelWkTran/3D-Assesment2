#include "Classes/Mesh.h"
#include "Classes/Player.h"
#include "GlobalVariables.h"

void FramebufferSizeCallback(GLFWwindow* _pWindow, int _iWidth, int _iHeight);

const float fMeshSize = 0.25f;
std::vector<stVertex> vVertices =
{
    //Coordinates                                      Normals                       Texture Cordinate
    stVertex{glm::vec3(-0.5f, 0.5f, 0.5f) * fMeshSize, glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec2(0.0f,1.0f)}, //Front
    stVertex{glm::vec3(-0.5f,-0.5f, 0.5f) * fMeshSize, glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec2(0.0f,0.0f)},
    stVertex{glm::vec3( 0.5f,-0.5f, 0.5f) * fMeshSize, glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec2(1.0f,0.0f)},
    stVertex{glm::vec3( 0.5f, 0.5f, 0.5f) * fMeshSize, glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec2(1.0f,1.0f)},
                                                   
    stVertex{glm::vec3( 0.5f, 0.5f,-0.5f) * fMeshSize, glm::vec3( 0.0f,-1.0f, 0.0f), glm::vec2(0.0f,1.0f)}, //Back
    stVertex{glm::vec3( 0.5f,-0.5f,-0.5f) * fMeshSize, glm::vec3( 0.0f,-1.0f, 0.0f), glm::vec2(0.0f,0.0f)},
    stVertex{glm::vec3(-0.5f,-0.5f,-0.5f) * fMeshSize, glm::vec3( 0.0f,-1.0f, 0.0f), glm::vec2(1.0f,0.0f)},
    stVertex{glm::vec3(-0.5f, 0.5f,-0.5f) * fMeshSize, glm::vec3( 0.0f,-1.0f, 0.0f), glm::vec2(1.0f,1.0f)},
                                                   
    stVertex{glm::vec3( 0.5f, 0.5f, 0.5f) * fMeshSize, glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec2(0.0f,1.0f)}, //Right
    stVertex{glm::vec3( 0.5f,-0.5f, 0.5f) * fMeshSize, glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec2(0.0f,0.0f)},
    stVertex{glm::vec3( 0.5f,-0.5f,-0.5f) * fMeshSize, glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec2(1.0f,0.0f)},
    stVertex{glm::vec3( 0.5f, 0.5f,-0.5f) * fMeshSize, glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec2(1.0f,1.0f)},
                                                   
    stVertex{glm::vec3(-0.5f, 0.5f,-0.5f) * fMeshSize, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f,1.0f)}, //Left
    stVertex{glm::vec3(-0.5f,-0.5f,-0.5f) * fMeshSize, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f,0.0f)},
    stVertex{glm::vec3(-0.5f,-0.5f, 0.5f) * fMeshSize, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f,0.0f)},
    stVertex{glm::vec3(-0.5f, 0.5f, 0.5f) * fMeshSize, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f,1.0f)},
                                                   
    stVertex{glm::vec3(-0.5f, 0.5f,-0.5f) * fMeshSize, glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec2(0.0f,1.0f)}, //Front
    stVertex{glm::vec3(-0.5f, 0.5f, 0.5f) * fMeshSize, glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec2(0.0f,0.0f)},
    stVertex{glm::vec3( 0.5f, 0.5f, 0.5f) * fMeshSize, glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec2(1.0f,0.0f)},
    stVertex{glm::vec3( 0.5f, 0.5f,-0.5f) * fMeshSize, glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec2(1.0f,1.0f)},
                                                   
    stVertex{glm::vec3(-0.5f,-0.5f, 0.5f) * fMeshSize, glm::vec3( 0.0f, 0.0f,-1.0f), glm::vec2(0.0f,1.0f)}, //Bottom
    stVertex{glm::vec3(-0.5f,-0.5f,-0.5f) * fMeshSize, glm::vec3( 0.0f, 0.0f,-1.0f), glm::vec2(0.0f,0.0f)},
    stVertex{glm::vec3( 0.5f,-0.5f,-0.5f) * fMeshSize, glm::vec3( 0.0f, 0.0f,-1.0f), glm::vec2(1.0f,0.0f)},
    stVertex{glm::vec3( 0.5f,-0.5f, 0.5f) * fMeshSize, glm::vec3( 0.0f, 0.0f,-1.0f), glm::vec2(1.0f,1.0f)}
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

stVertex stLightVertices[] =
{
    //Coordinates
    stVertex{glm::vec3(1.0f,  -1.0f, -1.0f) * 0.1f},
    stVertex{glm::vec3(-1.0f, -1.0f, -1.0f) * 0.1f},
    stVertex{glm::vec3(1.0f,  -1.0f,  1.0f) * 0.1f},
    stVertex{glm::vec3(-1.0f, -1.0f,  1.0f) * 0.1f},
    stVertex{glm::vec3(1.0f,   1.0f, -1.0f) * 0.1f},
    stVertex{glm::vec3(-1.0f,  1.0f, -1.0f) * 0.1f},
    stVertex{glm::vec3(1.0f,   1.0f,  1.0f) * 0.1f},
    stVertex{glm::vec3(-1.0f,  1.0f,  1.0f) * 0.1f}
};

GLuint GLuLightIndices[] =
{
    0, 2, 1, //Top
    1, 2, 3,
    6, 4, 7, //Bottom
    7, 4, 5,
    2, 7, 3, //Front
    2, 6, 7,
    4, 1, 5, //Back
    4, 0, 1,
    7, 5, 3, //Right Side
    3, 5, 1,
    4, 6, 0, //Left Side
    0, 6, 2
};

int main()
{
    //Initialize and Configure GLFW
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //Set up Window
    GLFWwindow* pWindow = glfwCreateWindow(uViewPortW, uViewPortH, "LearnOpenGL", NULL, NULL);
    if (pWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(pWindow);

    //Initializing GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    //Setup Window Viewport
    glViewport(0, 0, uViewPortW, uViewPortH);
    glfwSetFramebufferSizeCallback(pWindow, FramebufferSizeCallback);

    //Program Variables
    bool bWireframe = false;
    bool bCursorVisible = true;

    //Set up Textures
    GLuint m_GluTextureSlot = 0;
    CTexture Textures[]
    {
        CTexture("Textures/Planks.png", "Diffuse", m_GluTextureSlot++, GL_RGBA, GL_UNSIGNED_BYTE),
        CTexture("Textures/PlanksSpecular.png", "Specular", m_GluTextureSlot++, GL_RED, GL_UNSIGNED_BYTE)
    };
    
    //Set up Light Shader
    CShader ShaderLight("Shaders/Light.vert", "Shaders/Light.frag"); ShaderLight.Activate();
    std::vector<stVertex> vLightVerticies(stLightVertices, stLightVertices + sizeof(stLightVertices) / sizeof(stVertex));
    std::vector<GLuint> vLightIndicies(GLuLightIndices, GLuLightIndices + sizeof(GLuLightIndices) / sizeof(GLuint));
    std::vector<CTexture> vLightTextures;
    CMesh Light(vLightVerticies, vLightIndicies, vLightTextures, ShaderLight);

    glm::vec4 v4LightColour(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 v3LightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 mat4LightModel = glm::mat4(1.0f);
    mat4LightModel = glm::translate(mat4LightModel, v3LightPos);

    glUniformMatrix4fv(glGetUniformLocation(ShaderLight.GetID(), "uni_mat4Model"), 1, GL_FALSE, glm::value_ptr(mat4LightModel));
    glUniform4f(glGetUniformLocation(ShaderLight.GetID(), "uni_v4LightColor"), v4LightColour.x, v4LightColour.y, v4LightColour.z, v4LightColour.w);
    
    //Set up Cube Shader
    CShader ShaderCube("Shaders/Default.vert", "Shaders/Default.frag"); ShaderCube.Activate();
    std::vector<CTexture> vTextures(Textures, Textures + sizeof(Textures) / sizeof(CTexture));
    CMesh Cube(vVertices, vIndices, vTextures, ShaderCube);

    float mat4CubeRotation = 0;
    glm::mat4 mat4CubePosition  = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.25f));
    glm::mat4 mat4CubePosition2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, 0.0f, 0.0f));
    glm::mat4 mat4CubeModel = mat4CubePosition;

    glUniform4f(glGetUniformLocation(ShaderCube.GetID(), "uni_v4LightColor"), v4LightColour.x, v4LightColour.y, v4LightColour.z, v4LightColour.w);
    glUniform3f(glGetUniformLocation(ShaderCube.GetID(), "uni_v3LightPosition"), v3LightPos.x, v3LightPos.y, v3LightPos.z);

    //Setup Player
    CPlayer m_Player;
    m_Player.SetShader(ShaderCube);

    //Set up camera
    CCamera Camera(&uViewPortW, &uViewPortH, true, glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    glfwSetKeyCallback(pWindow, KeyFunction);

    //Render Loop
    while (!glfwWindowShouldClose(pWindow))
    {
        //Calculate Deltatime
        float fCurrentTimestep = (float)glfwGetTime();
        fDeltatime = fCurrentTimestep - fPreviousTimestep;
        fPreviousTimestep = fCurrentTimestep;
        
        if (bKeyPressed == false && iAction != GLFW_RELEASE)
        {
            switch (iKey)
            {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(pWindow, true);
                break;
            case GLFW_KEY_X:
                bWireframe = !bWireframe;
                if (bWireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
            case GLFW_KEY_C:
                bCursorVisible = !bCursorVisible;
                if (bCursorVisible) glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL); else glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
                break;
            }
        }

        Camera.Update();
        m_Player.Input(pWindow);
        UpdateKeyPressed();

        //Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ShaderCube.Activate();
        mat4CubeModel = glm::rotate(mat4CubePosition, glm::radians(mat4CubeRotation += fDeltatime * 45.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::inverse(mat4CubePosition);
        glUniformMatrix4fv(glGetUniformLocation(ShaderCube.GetID(), "uni_mat4Model"), 1, GL_FALSE, glm::value_ptr(mat4CubeModel));
        Cube.Draw(Camera);
        
        mat4CubeModel = glm::rotate(mat4CubePosition2, glm::radians(mat4CubeRotation += fDeltatime * 45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::inverse(mat4CubePosition2);
        glUniformMatrix4fv(glGetUniformLocation(ShaderCube.GetID(), "uni_mat4Model"), 1, GL_FALSE, glm::value_ptr(mat4CubeModel));
        Cube.Draw(Camera);

        m_Player.Draw(Camera);
        
        Light.Draw(Camera);

        //Check and call events and swap the buffers
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(pWindow);
    glfwTerminate();
    return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}