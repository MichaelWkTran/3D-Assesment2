#include "Texture.h"

/*static */std::map<GLuint, CTexture*> CTextureManager::mapTextures;

/*static */bool CTextureManager::Empty()
{
	return mapTextures.empty();
}

/*static */unsigned int CTextureManager::Size()
{
	return mapTextures.size();
}

/*static */unsigned int CTextureManager::MaxSize()
{
	return mapTextures.max_size();
}

CTexture* CTextureManager::operator[](unsigned int _GLuID)
{
	return At(_GLuID);
}

/*static */CTexture* CTextureManager::At(unsigned int _GLuID)
{
	CTexture* pOutput = nullptr;
	
	try { pOutput = mapTextures.at(_GLuID); }
	catch (const std::out_of_range& oor) { std::cout << "OUT OF RANGE ERROR: " << oor.what() << '\n'; pOutput = nullptr; }
	
	return pOutput;
}

CTexture* CTextureManager::Insert(const char* _pType, GLuint&& _GLuSlot, const char* _pName)
{
	CTexture* pTexture = new CTexture(_pName, _pType, std::move(_GLuSlot));
	mapTextures.insert(std::pair<GLuint, CTexture*>(pTexture->GetID(), pTexture));

	return pTexture;
}

/*static */CTexture* CTextureManager::Insert(const char* _pImage, const char* _pType, GLuint&& _GLuSlot, GLenum&& _GLeFormat, GLenum&& _GLePixelType, const char* _pName/* = ""*/)
{
	GLenum GLeFormat = _GLeFormat; GLenum GLePixelType = _GLePixelType;

	CTexture* pTexture = new CTexture(_pName, _pType, std::move(_GLuSlot));
	mapTextures.insert(std::pair<GLuint, CTexture*>(pTexture->GetID(), pTexture));

	int iImageWidth, iImageHeight, iColChanNum;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pImageData = stbi_load(_pImage, &iImageWidth, &iImageHeight, &iColChanNum, 0);

	pTexture->Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iImageWidth, iImageHeight, 0, GLeFormat, GLePixelType, pImageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(pImageData);
	Unbind();

	return pTexture;
}

/*static */void CTextureManager::Erase(unsigned int _GLuID)
{
	auto Iterator = mapTextures.find(_GLuID);
	if (Iterator == mapTextures.end()) return void();

	delete (*Iterator).second;
	(*Iterator).second = nullptr;
	mapTextures.erase(Iterator);
}

/*static */void CTextureManager::Clear()
{
	for (auto& Texture : mapTextures)
	{
		if (Texture.second != nullptr) delete Texture.second;
		Texture.second = nullptr;
	}

	mapTextures.clear();
}

/*static */void CTextureManager::Bind(unsigned int _GLuID)
{
	At(_GLuID)->Bind();
}

/*static */void CTextureManager::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

CTexture::CTexture(const char* _pName, const char* _pType, GLuint&& _GLuSlot)
{
	glGenTextures(1, &m_GLuID);
	m_pName = _pName;
	m_pType = _pType;
	m_GLuUnit = _GLuSlot;

	_GLuSlot = 0U;
}

CTexture::~CTexture()
{
	glDeleteTextures(1, &m_GLuID);
}

const GLuint CTexture::GetID() const
{
	return m_GLuID;
}

void CTexture::Bind() const
{
	glActiveTexture(GL_TEXTURE0 + m_GLuUnit);
	glBindTexture(GL_TEXTURE_2D, m_GLuID);
}

/*static */void CTexture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}