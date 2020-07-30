#pragma once
#include <GL/glew.h>
#include <stb_image.h>
#include <string>
#include "Renderer/Texture.h"

namespace Engine
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& path);
		~OpenGLTexture();
		virtual void Bind(unsigned int slot) override;
		virtual void Unbind() override;
		virtual inline unsigned int GetId() override { return m_Id; }

	private:
		unsigned int m_Id;
		int m_Width, m_Height, m_Channels;
	};
}