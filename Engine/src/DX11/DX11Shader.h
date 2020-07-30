#pragma once
#include "Renderer/Shader.h"
#include "DX11/DX11RenderingApi.h"

namespace Engine {

	class DX11Shader : public Shader
	{
	public:
		DX11Shader(const std::string& VertexPath, const std::string& PixelPath);
		~DX11Shader();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual std::string fromFile(const std::string& path) override;

	private:
		ID3D11VertexShader* m_VertexShader;
		ID3D11PixelShader* m_PixelShader;
	};

}