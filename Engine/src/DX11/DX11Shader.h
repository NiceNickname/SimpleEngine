#pragma once
#include "Renderer/Shader.h"
#include "DX11RenderingApi.h"
#include "DX11ConstantBuffer.h"



namespace Engine {

	// TODO: add constant buffers support
	class DX11Shader : public Shader
	{
	public:
		DX11Shader(const std::string& VertexPath, const std::string& PixelPath);
		~DX11Shader();

		virtual void Bind() override;
		virtual void Unbind() override;
		ID3DBlob* GetVSCode() { return m_VSCode; }
		ID3DBlob* GetPSCode() { return m_PSCode; }

		virtual void SetUniform1i(const std::string& name, int value) override;

		virtual void SetUniform1f(const std::string& name, float value) override;
		virtual void SetUniform2f(const std::string& name, const glm::vec2& value) override;
		virtual void SetUniform3f(const std::string& name, const glm::vec3& value) override;
		virtual void SetUniform4f(const std::string& name, const glm::vec4& value) override;

		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& value) override;

		virtual void SetUniformLayout(UniformElement* layout, unsigned int count) override;

	private:
		virtual std::string fromFile(const std::string& path) override;
		virtual int GetUniform(const std::string& name) override;
	private:
		ID3D11VertexShader* m_VertexShader;
		ID3D11PixelShader* m_PixelShader;

		ID3DBlob* m_VSCode;
		ID3DBlob* m_PSCode;

		std::vector<std::unique_ptr<DX11ConstantBuffer>> m_Cbuffers;
		
	};

}