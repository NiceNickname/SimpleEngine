#include "pch.h"
#include "DX11Shader.h"
#include "Renderer/Renderer2D.h"
#include <glm/gtc/type_ptr.hpp>

namespace Engine {



	DX11Shader::DX11Shader(const std::string& VertexPath, const std::string& PixelPath)
	{
		// converting into WideString because D3DReadFileToBlob needs a WideString
		size_t strSize = strlen(VertexPath.c_str()) + 1;
		std::wstring WideVertexPath(strSize, L'#');
		mbstowcs(&WideVertexPath[0], VertexPath.c_str(), strSize);

		D3DReadFileToBlob(WideVertexPath.c_str(), &m_VSCode);

		strSize = strlen(PixelPath.c_str()) + 1;
		std::wstring WidePixelPath(strSize, L'#');
		mbstowcs(&WidePixelPath[0], PixelPath.c_str(), strSize);

		D3DReadFileToBlob(WidePixelPath.c_str(), &m_PSCode);
		

		DX11RenderingApi::GetDevice()->CreateVertexShader(m_VSCode->GetBufferPointer(), m_VSCode->GetBufferSize(), NULL, &m_VertexShader);
		DX11RenderingApi::GetDevice()->CreatePixelShader(m_PSCode->GetBufferPointer(), m_PSCode->GetBufferSize(), NULL, &m_PixelShader);


		DX11RenderingApi::GetContext()->VSSetShader(m_VertexShader, 0, 0);
		DX11RenderingApi::GetContext()->PSSetShader(m_PixelShader, 0, 0);

		
	}

	DX11Shader::~DX11Shader()
	{
		m_VSCode->Release();
		m_PSCode->Release();
		m_VertexShader->Release();
		m_PixelShader->Release();
	}

	void DX11Shader::Bind()
	{
		DX11RenderingApi::GetContext()->VSSetShader(m_VertexShader, 0, 0);
		DX11RenderingApi::GetContext()->PSSetShader(m_PixelShader, 0, 0);


		for (int i = 0; i < m_Cbuffers.size(); i++)
		{
			m_Cbuffers[i]->Bind(i);
		}

	}

	void DX11Shader::Unbind()
	{

	}

	std::string DX11Shader::fromFile(const std::string& path)
	{
		return "this function is not used in dx11\n";
	}

	int DX11Shader::GetUniform(const std::string& name)
	{
		for (int i = 0; i < m_Cbuffers.size(); i++)
		{
			if (name == m_Cbuffers[i]->GetName())
				return i;
		}
		return -1;
	}

	void DX11Shader::SetUniform1i(const std::string& name, int value)
	{
		int index = GetUniform(name);

		if (index == -1)
			std::cout << "no such uniform\n";

		m_Cbuffers[index]->Update((const void*)&value);
	}

	void DX11Shader::SetUniform1f(const std::string& name, float value)
	{
		int index = GetUniform(name);

		if (index == -1)
			std::cout << "no such uniform\n";

		m_Cbuffers[index]->Update((const void*)&value);
	}

	void DX11Shader::SetUniform2f(const std::string& name, const glm::vec2& value)
	{
		int index = GetUniform(name);

		if (index == -1)
			std::cout << "no such uniform\n";

		m_Cbuffers[index]->Update((const void*)glm::value_ptr(value));
	}

	void DX11Shader::SetUniform3f(const std::string& name, const glm::vec3& value)
	{
		int index = GetUniform(name);

		if (index == -1)
			std::cout << "no such uniform\n";

		m_Cbuffers[index]->Update((const void*)glm::value_ptr(value));
	}

	void DX11Shader::SetUniform4f(const std::string& name, const glm::vec4& value)
	{
		int index = GetUniform(name);

		if (index == -1)
			std::cout << "no such uniform\n";

		m_Cbuffers[index]->Update((const void*)glm::value_ptr(value));
	}

	void DX11Shader::SetUniformMat4f(const std::string& name, const glm::mat4& value)
	{
		int index = GetUniform(name);

		if (index == -1)
			std::cout << "no such uniform\n";
		
		m_Cbuffers[index]->Update((const void*)glm::value_ptr(value));

	}

	void DX11Shader::SetUniformLayout(UniformElement* layout, unsigned int count)
	{
		for (int i = 0; i < count; i++)
		{
			int UniformSize = 0;
			if (layout[i].type == DATATYPE::FLOAT1)
				UniformSize = sizeof(float);
			else if (layout[i].type == DATATYPE::FLOAT2)
				UniformSize = sizeof(float) * 2;
			else if (layout[i].type == DATATYPE::FLOAT3)
				UniformSize = sizeof(float) * 3;
			else if (layout[i].type == DATATYPE::FLOAT4)
				UniformSize = sizeof(float) * 4;
			else if (layout[i].type == DATATYPE::MAT4)
				UniformSize = sizeof(float) * 4 * 4;
			else if (layout[i].type == DATATYPE::INT1)
				UniformSize = sizeof(int);

			m_Cbuffers.push_back(std::make_unique<DX11ConstantBuffer>(layout[i].name, UniformSize));
		}
	}

}