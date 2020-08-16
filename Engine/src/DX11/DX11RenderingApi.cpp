#include "pch.h"

#include "DX11RenderingApi.h"

#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_dx11.h"

#include "glm/gtc/type_ptr.hpp"

#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace Engine {

	DX11RenderingApi::DX11RenderingApi(const std::unique_ptr<Window>& window)
	{

		s_Hwnd = static_cast<Win32Window*>(window.get())->GetHwnd();
		InitD3D(s_Hwnd);

		// Show the window
		::ShowWindow(s_Hwnd, SW_SHOWDEFAULT);
		::UpdateWindow(s_Hwnd);

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
		ImGui_ImplWin32_Init(s_Hwnd);
		ImGui_ImplDX11_Init(s_Device, s_Context);
	}

	DX11RenderingApi::~DX11RenderingApi()
	{
		ShutDown();
	}

	void DX11RenderingApi::SetClearColor(const glm::vec4& color)
	{
		s_ClearColor = color;
	}

	// TODO: take color as a parameter
	void DX11RenderingApi::ClearBuffer()
	{
		s_Context->ClearRenderTargetView(s_BackBuffer, glm::value_ptr(s_ClearColor));

		s_Context->ClearDepthStencilView(s_ZBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	


	void DX11RenderingApi::SetVSync(bool enabled)
	{
		s_VSyncEnabled = enabled;
	}

	void DX11RenderingApi::Prepare()
	{
		s_Context->OMSetRenderTargets(1, &s_BackBuffer, s_ZBuffer);
		ClearBuffer();
	}

	void DX11RenderingApi::ShutDown()
	{
		s_SwapChain->SetFullscreenState(FALSE, NULL);

		ImGui_ImplDX11_Shutdown();

		s_BS->Release();
		s_SS->Release();
		s_BS->Release();
		s_BackBuffer->Release();
		s_SwapChain->Release();
		s_Context->Release();
		s_Device->Release();
		s_ZBuffer->Release();
	}

	void DX11RenderingApi::SwapBuffers()
	{
		if (s_VSyncEnabled)
			s_SwapChain->Present(1, 0);
		else
			s_SwapChain->Present(0, 0);
	}

	void DX11RenderingApi::InitD3D(HWND hwnd)
	{
		// get user's screen resolution
		RECT ScreenSize;
		HWND desktop = GetDesktopWindow();
		GetWindowRect(desktop, &ScreenSize);

		s_ScreenWidth = ScreenSize.right - ScreenSize.left;
		s_ScreenHeight = ScreenSize.bottom - ScreenSize.top;

		// get user's refresh rate
		IDXGIFactory* factory;
		IDXGIAdapter* adapter;
		IDXGIOutput* adapterOutput;
		unsigned int displatModesCount;

		CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
		factory->EnumAdapters(0, &adapter);
		adapter->EnumOutputs(0, &adapterOutput);
		adapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8X8_UNORM, DXGI_ENUM_MODES_INTERLACED, &displatModesCount, NULL);
		auto* displayModeList = new DXGI_MODE_DESC[displatModesCount];
		adapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8X8_UNORM, DXGI_ENUM_MODES_INTERLACED, &displatModesCount, displayModeList);

		for (int i = 0; i < displatModesCount; i++)
		{
			if (displayModeList[i].Width == s_ScreenWidth)
			{
				if (displayModeList[i].Height == s_ScreenHeight)
				{
					s_Numerator = displayModeList[i].RefreshRate.Numerator;
					s_Denominator = displayModeList[i].RefreshRate.Denominator;
				}
			}
		}

		adapterOutput->Release();
		adapter->Release();
		factory->Release();
		delete[] displayModeList;


		// Setup swap chain
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 2;
		sd.BufferDesc.Width = s_ScreenWidth;
		sd.BufferDesc.Height = s_ScreenHeight;
		sd.BufferDesc.RefreshRate.Denominator = s_Denominator;
		sd.BufferDesc.RefreshRate.Numerator = s_Numerator;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
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
			featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &s_SwapChain, &s_Device, &featureLevel, &s_Context);


		// set backbuffer as render target
		ID3D11Texture2D* pBackBuffer;
		s_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		s_Device->CreateRenderTargetView(pBackBuffer, NULL, &s_BackBuffer);
		pBackBuffer->Release();

		// viewport (mapping NDC to pixel coordinates)
		D3D11_VIEWPORT viewport;

		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = s_ScreenWidth;
		viewport.Height = s_ScreenHeight;
		viewport.MinDepth = 0;
		viewport.MaxDepth = 1;

		s_Context->RSSetViewports(1, &viewport);


		// depth buffer
		D3D11_TEXTURE2D_DESC texd;
		ZeroMemory(&texd, sizeof(texd));

		texd.Width = s_ScreenWidth;
		texd.Height = s_ScreenHeight;
		texd.ArraySize = 1;
		texd.MipLevels = 1;
		texd.SampleDesc.Count = 1;
		texd.Format = DXGI_FORMAT_D32_FLOAT;
		texd.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		ID3D11Texture2D* pDepthBuffer;
		s_Device->CreateTexture2D(&texd, NULL, &pDepthBuffer);

		
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));

		dsvd.Format = DXGI_FORMAT_D32_FLOAT;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

		s_Device->CreateDepthStencilView(pDepthBuffer, &dsvd, &s_ZBuffer);
		pDepthBuffer->Release();

		InitStates();

		s_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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


		s_Device->CreateRasterizerState(&rd, &s_RS);
		s_Context->RSSetState(s_RS);

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

		s_Device->CreateSamplerState(&sd, &s_SS);
		s_Context->PSSetSamplers(0, 1, &s_SS);

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

		s_Device->CreateBlendState(&bd, &s_BS);
		s_Context->OMSetBlendState(s_BS, 0, 0xffffffff);
	}

	ID3D11Device* DX11RenderingApi::s_Device;

	ID3D11DeviceContext* DX11RenderingApi::s_Context;

	IDXGISwapChain* DX11RenderingApi::s_SwapChain;

	ID3D11RenderTargetView* DX11RenderingApi::s_BackBuffer;

	ID3D11RasterizerState* DX11RenderingApi::s_RS;

	ID3D11SamplerState* DX11RenderingApi::s_SS;

	ID3D11BlendState* DX11RenderingApi::s_BS;

	ID3D11DepthStencilView* DX11RenderingApi::s_ZBuffer;

	HWND DX11RenderingApi::s_Hwnd;

	unsigned int DX11RenderingApi::s_ScreenWidth;

	unsigned int DX11RenderingApi::s_ScreenHeight;

	unsigned int DX11RenderingApi::s_Denominator;
	
	unsigned int DX11RenderingApi::s_Numerator;

	bool DX11RenderingApi::s_VSyncEnabled = false;

	glm::vec4 DX11RenderingApi::s_ClearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
}



