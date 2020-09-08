#include "pch.h"

#include "OpenGLTexture.h"

#include "glad/glad.h"

namespace Engine
{
	OpenGLTexture::OpenGLTexture(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
	
		data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 4);
	
		glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);

		glTextureStorage2D(m_Id, 1, GL_RGBA8, m_Width, m_Height);

		glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_Id, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	

		stbi_image_free(data);
	
	}
	
	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_Id);
	}
	
	void OpenGLTexture::Bind(unsigned int slot)
	{
		glBindTextureUnit(slot, m_Id);
	}

	void OpenGLTexture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

