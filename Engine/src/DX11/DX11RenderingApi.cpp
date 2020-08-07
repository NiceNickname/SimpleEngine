#include "pch.h"

#include "DX11RenderingApi.h"

#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_dx11.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace Engine {

	DX11RenderingApi::DX11RenderingApi(const std::unique_ptr<Window>& window)
	{

		hwnd = static_cast<Win32Window*>(window.get())->GetHwnd();
		InitD3D(hwnd);

		// Show the window
		::ShowWindow(hwnd, SW_SHOWDEFAULT);
		::UpdateWindow(hwnd);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;
		//io.ConfigViewportsNoDefaultParent = true;
		//io.ConfigDockingAlwaysTabBar = true;
		//io.ConfigDockingTransparentPayload = true;


	// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer bindings
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX11_Init(m_Device, m_Context);
	}

	DX11RenderingApi::~DX11RenderingApi()
	{
		ShutDown();
	}

	void DX11RenderingApi::ClearBuffer()
	{
		float color[] = { 0.0f, 0.2f, 0.4f, 1.0f };
		// clear the back buffer to a deep blue
		m_Context->ClearRenderTargetView(m_BackBuffer, color);
	}
	


	void DX11RenderingApi::Render()
	{
		m_Context->OMSetRenderTargets(1, &m_BackBuffer, NULL);
		ClearBuffer();
	}

	void DX11RenderingApi::ShutDown()
	{
		m_SwapChain->SetFullscreenState(FALSE, NULL);

		ImGui_ImplDX11_Shutdown();

		m_BS->Release();
		m_SS->Release();
		m_BS->Release();
		m_BackBuffer->Release();
		m_SwapChain->Release();
		m_Context->Release();
		m_Device->Release();
	}

	void DX11RenderingApi::SwapBuffers()
	{
		m_SwapChain->Present(1, 0);
	}

	void DX11RenderingApi::InitD3D(HWND hwnd)
	{
		// Setup swap chain
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 2;
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT createDeviceFlags = 0;
		//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
		D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags,
			featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &m_SwapChain, &m_Device, &featureLevel, &m_Context);


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
		viewport.Width = 1280;
		viewport.Height = 800;

		m_Context->RSSetViewports(1, &viewport);

		InitStates();

		m_Context->OMSetRenderTargets(1, &m_BackBuffer, NULL);
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

	HWND DX11RenderingApi::hwnd;

}



