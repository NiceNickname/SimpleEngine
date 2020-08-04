#pragma once
#include "Renderer/Shader.h"
#include "DX11RenderingApi.h"



namespace Engine {

	// TODO: add constant buffers support
	class DX11Shader : public Shader
	{
	public:
		DX11Shader(const std::string& VertexPath, const std::string& PixelPath);
		~DX11Shader();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual std::string fromFile(const std::string& path) override;
		ID3DBlob* GetVSCode() { return m_VSCode; }
		ID3DBlob* GetPSCode() { return m_PSCode; }

	private:
		ID3D11VertexShader* m_VertexShader;
		ID3D11PixelShader* m_PixelShader;

		ID3DBlob* m_VSCode;
		ID3DBlob* m_PSCode;
		
	};

}