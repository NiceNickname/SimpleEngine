#pragma once
#include <GL/glew.h>
#include <stb_image.h>
#include <string>

namespace Engine
{
	class OpenGLTexture
	{
	public:
		OpenGLTexture(const std::string& path);
		~OpenGLTexture();
		void Bind(unsigned int slot);
		inline unsigned int GetId() { return m_Id; }

	private:
		unsigned int m_Id;
		int m_Width, m_Height, m_Channels;
	};
}