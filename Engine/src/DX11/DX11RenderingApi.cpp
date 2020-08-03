#include "pch.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GL/glew.h>
#include "DX11RenderingApi.h"
#include <GLFW/glfw3.h>
#include "GLFW/glfw3native.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

namespace Engine {

	DX11RenderingApi::DX11RenderingApi(GLFWwindow* window)
	{
		Init(window);
	}

	DX11RenderingApi::~DX11RenderingApi()
	{

	}

	void DX11RenderingApi::ClearBuffer()
	{
		// clear the back buffer to a deep blue
		m_Context->ClearRenderTargetView(m_BackBuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

		// clear the depth buffer
		m_Context->ClearDepthStencilView(m_Zbuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	

	void DX11RenderingApi::Init(GLFWwindow* window)
	{
		InitD3D(window);
	}

	void DX11RenderingApi::ShutDown()
	{
		m_SwapChain->SetFullscreenState(FALSE, NULL);

		m_VSCode->Release();
		m_PSCode->Release();
		m_Zbuffer->Release();
		m_BS->Release();
		m_SS->Release();
		m_BS->Release();
		m_BackBuffer->Release();
		m_SwapChain->Release();
		m_Context->Release();
		m_Device->Release();
	}

	void DX11RenderingApi::SwapBuffers(unsigned int SyncInterval, unsigned int Flags)
	{
		m_SwapChain->Present((UINT)SyncInterval, (UINT)Flags);
	}

	void DX11RenderingApi::InitD3D(GLFWwindow* window)
	{
		DXGI_SWAP_CHAIN_DESC scd;

		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

		scd.BufferCount = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.Width = SCREEN_WIDTH;
		scd.BufferDesc.Height = SCREEN_HEIGHT;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = glfwGetWin32Window(window);
		scd.SampleDesc.Count = 4;
		scd.Windowed = TRUE;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			D3D11_CREATE_DEVICE_DEBUG,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&scd,
			&m_SwapChain,
			&m_Device,
			NULL,
			&m_Context
		);

		// set backbuffer as render target
		ID3D11Texture2D* pBackBuffer;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		m_Device->CreateRenderTargetView(pBackBuffer, NULL, &m_BackBuffer);
		pBackBuffer->Release();

		// viewport (mapping NDC to pixel coordinates)
		D3D11_VIEWPORT viewport;

		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = SCREEN_WIDTH;
		viewport.Height = SCREEN_HEIGHT;
		viewport.MinDepth = 0;
		viewport.MaxDepth = 1;

		m_Context->RSSetViewports(1, &viewport);

		InitStates();


		D3D11_TEXTURE2D_DESC texd;

		ZeroMemory(&texd, sizeof(D3D11_TEXTURE2D_DESC));

		texd.Width = SCREEN_WIDTH;
		texd.Height = SCREEN_HEIGHT;
		texd.ArraySize = 1;
		texd.Format = DXGI_FORMAT_D32_FLOAT;
		texd.MipLevels = 1;
		texd.SampleDesc.Count = 4;
		texd.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		ID3D11Texture2D* pDepthBuffer;
		m_Device->CreateTexture2D(&texd, NULL, &pDepthBuffer);

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;

		ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

		dsvd.Format = DXGI_FORMAT_D32_FLOAT;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

		m_Device->CreateDepthStencilView(pDepthBuffer, &dsvd, &m_Zbuffer);

		pDepthBuffer->Release();

		m_Context->OMSetRenderTargets(1, &m_BackBuffer, m_Zbuffer);
		m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		
	}

	void DX11RenderingApi::InitStates()
	{
		
		D3D11_RASTERIZER_DESC rd;

		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_BACK;
		rd.FrontCounterClockwise = FALSE;
		rd.DepthClipEnable = TRUE;
		rd.ScissorEnable = FALSE;
		rd.AntialiasedLineEnable = TRUE;
		rd.MultisampleEnable = FALSE;
		rd.DepthBias = 0;
		rd.DepthBiasClamp = 0.0f;
		rd.SlopeScaledDepthBias = 0.0f;


		m_Device->CreateRasterizerState(&rd, &m_RS);
		m_Context->RSSetState(m_RS);

		D3D11_SAMPLER_DESC sd;

		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sd.MaxAnisotropy = 8;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.BorderColor[0] = 1.0f;
		sd.BorderColor[1] = 1.0f;
		sd.BorderColor[2] = 1.0f;
		sd.BorderColor[3] = 1.0f;
		sd.MinLOD = 0.0f;
		sd.MaxLOD = FLT_MAX;
		sd.MipLODBias = 0.0f;

		m_Device->CreateSamplerState(&sd, &m_SS);
		m_Context->PSSetSamplers(0, 1, &m_SS);

		D3D11_BLEND_DESC bd;
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		bd.IndependentBlendEnable = FALSE;
		bd.AlphaToCoverageEnable = FALSE;

		m_Device->CreateBlendState(&bd, &m_BS);
		m_Context->OMSetBlendState(m_BS, 0, 0xffffffff);
	}

	ID3D11Device* DX11RenderingApi::m_Device;

	ID3D11DeviceContext* DX11RenderingApi::m_Context;

	IDXGISwapChain* DX11RenderingApi::m_SwapChain;

	ID3D11RenderTargetView* DX11RenderingApi::m_BackBuffer;

	ID3D11RasterizerState* DX11RenderingApi::m_RS;

	ID3D11SamplerState* DX11RenderingApi::m_SS;

	ID3D11BlendState* DX11RenderingApi::m_BS;

	ID3D11DepthStencilView* DX11RenderingApi::m_Zbuffer;

	ID3D10Blob* DX11RenderingApi::m_VSCode;

	ID3D10Blob* DX11RenderingApi::m_PSCode;

}



