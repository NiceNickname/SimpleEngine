#pragma once
#include "Renderer/Texture.h"

namespace Engine {

	class DX11Texture : public Texture
	{
		static unsigned int id;
	public:
		DX11Texture(const std::string& path);
		~DX11Texture();

		virtual void Bind(unsigned int slot) override;
		virtual void Unbind() override;
		virtual unsigned int GetId() override;

	private:
		ID3D11ShaderResourceView* m_Texture;
		unsigned int m_Id;
	};

}
