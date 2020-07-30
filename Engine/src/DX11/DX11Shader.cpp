#include "pch.h"
#include "DX11RenderingApi.h"
#include "DX11Shader.h"

namespace Engine {


	DX11Shader::DX11Shader(const std::string& VertexPath, const std::string& PixelPath)
	{
		ID3D10Blob* VS = DX11RenderingApi::GetVSCode();
		ID3D10Blob* PS = DX11RenderingApi::GetPSCode();
		D3DX10CompileFromFile(VertexPath.c_str(), 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
		D3DX10CompileFromFile(PixelPath.c_str(), 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

		DX11RenderingApi::GetDevice()->CreateVertexShader(DX11RenderingApi::GetVSCode()->GetBufferPointer(), DX11RenderingApi::GetVSCode()->GetBufferSize(), NULL, &m_VertexShader);
		DX11RenderingApi::GetDevice()->CreatePixelShader(DX11RenderingApi::GetPSCode()->GetBufferPointer(), DX11RenderingApi::GetPSCode()->GetBufferSize(), NULL, &m_PixelShader);

		DX11RenderingApi::GetContext()->VSSetShader(m_VertexShader, 0, 0);
		DX11RenderingApi::GetContext()->PSSetShader(m_PixelShader, 0, 0);
	}

	DX11Shader::~DX11Shader()
	{
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