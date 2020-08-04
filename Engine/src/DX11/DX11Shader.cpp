#include "pch.h"
#include "DX11Shader.h"


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
	}

	void DX11Shader::Unbind()
	{

	}

	std::string DX11Shader::fromFile(const std::string& path)
	{
		return "Don't use this function with DX11\n";
	}

}