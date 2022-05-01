#include "Shader.h"

void CShader::CompileErrors(unsigned int _uShader, const char* _pType)
{
	GLint GLiHasCompiled;
	char cInfoLog[1024];

	if (_pType != "PROGRAM")
	{
		glGetShaderiv(_uShader, GL_COMPILE_STATUS, &GLiHasCompiled);
		if (GLiHasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(_uShader, 1024, NULL, cInfoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << _pType << "\n" << cInfoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(_uShader, GL_LINK_STATUS, &GLiHasCompiled);
		if (GLiHasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(_uShader, 1024, NULL, cInfoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << _pType << "\n" << cInfoLog << std::endl;
		}
	}
}

/*static */std::string CShader::GetFileContents(const char* _pFileName)
{
	std::ifstream In(_pFileName, std::ios::binary);
	if (In)
	{
		std::string strContents;
		In.seekg(0, std::ios::end);
		strContents.resize((unsigned int)In.tellg());
		In.seekg(0, std::ios::beg);
		In.read(&strContents[0], strContents.size());
		In.close();
		return strContents;
	}
	throw errno;
}

CShader::CShader(const char* _pVertexFile, const char* _pFragmentFile, const char* _pGeometryFile/* = ""*/)
{
	//Set up Shaders
	std::string strVertexCode = GetFileContents(_pVertexFile); const char* pVertexSource = strVertexCode.c_str();
	GLuint GLuVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(GLuVertexShader, 1, &pVertexSource, NULL);
	glCompileShader(GLuVertexShader);
	CompileErrors(GLuVertexShader, "VERTEX");

	std::string strFragmentCode = GetFileContents(_pFragmentFile); const char* pFragmentSource = strFragmentCode.c_str();
	GLuint GLuFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(GLuFragmentShader, 1, &pFragmentSource, NULL);
	glCompileShader(GLuFragmentShader);
	CompileErrors(GLuFragmentShader, "FRAGMENT");

	GLuint GLuGeometryShader = 0;
	if (_pGeometryFile == "")
	{
		m_bUsesGeometryShader = false;
	}
	else
	{
		m_bUsesGeometryShader = true;
		std::string strGeometryCode = GetFileContents(_pGeometryFile); const char* pGeometrySource = strGeometryCode.c_str();
		GLuGeometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(GLuGeometryShader, 1, &pGeometrySource, NULL);
		glCompileShader(GLuGeometryShader);
		CompileErrors(GLuGeometryShader, "GEOMETRY");
	}

	//Create and link to Program
	m_GLuID = glCreateProgram();

	glAttachShader(m_GLuID, GLuVertexShader);
	glAttachShader(m_GLuID, GLuFragmentShader);
	if (m_bUsesGeometryShader) glAttachShader(m_GLuID, GLuGeometryShader);

	glLinkProgram(m_GLuID);
	CompileErrors(m_GLuID, "PROGRAM");

	glDeleteShader(GLuVertexShader);
	glDeleteShader(GLuFragmentShader);
	if (m_bUsesGeometryShader) glDeleteShader(GLuGeometryShader);
}

CShader::~CShader()
{
	glDeleteProgram(m_GLuID);
}

void CShader::Activate()
{
	GLint GluCurrentProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &GluCurrentProgram);
	if (GluCurrentProgram == m_GLuID) return void();

	glUseProgram(m_GLuID);
}

void CShader::Deactivate()
{
	GLint GluCurrentProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &GluCurrentProgram);
	if (GluCurrentProgram == 0) return void();

	glUseProgram(0);
}

const GLuint& CShader::GetID()
{
	return m_GLuID;
}