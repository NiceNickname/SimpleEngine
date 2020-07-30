#pragma once

namespace Engine {

	class Texture
	{
	public:
		static Texture* Create(const std::string& path);
		virtual void Bind(unsigned int slot) = 0;
		virtual void Unbind() = 0;
		virtual unsigned int GetId() { return 0; }

	protected:
		int m_Width, m_Height, m_Channels;
	};

}