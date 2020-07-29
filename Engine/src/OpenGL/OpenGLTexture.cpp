#include "pch.h"

#include "OpenGLTexture.h"

namespace Engine
{
	OpenGLTexture::OpenGLTexture(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
	
		data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 4);
	
		glGenTextures(1, &m_Id);
	
		glBindTexture(GL_TEXTURE_2D, m_Id);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	
	}
	
	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_Id);
	}
	
	void OpenGLTexture::Bind(unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
	
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}
}

