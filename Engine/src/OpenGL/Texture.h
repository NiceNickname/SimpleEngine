#pragma once
#include <GL/glew.h>
#include <stb_image.h>
#include <string>

namespace Engine
{
	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();
		void Bind(unsigned int slot);
		inline unsigned int GetId() { return m_Id; }

	private:
		unsigned int m_Id;
		int m_Width, m_Height, m_Channels;
	};
}