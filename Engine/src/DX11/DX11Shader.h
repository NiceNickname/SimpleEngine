#pragma once
#include "Renderer/Shader.h"
#include "DX11RenderingApi.h"
#include "DX11ConstantBuffer.h"

#include <unordered_map>



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

		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& value) override;

	private:
		ID3D11VertexShader* m_VertexShader;
		ID3D11PixelShader* m_PixelShader;

		ID3DBlob* m_VSCode;
		ID3DBlob* m_PSCode;

		std::unordered_map<std::string, DX11ConstantBuffer*> m_Cbuffers;
		
	};

}