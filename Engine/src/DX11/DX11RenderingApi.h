#pragma once
#include "Renderer/RenderingAPI.h"

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

namespace Engine {

	class DX11RenderingApi  : public RenderingAPI 
	{

	public:
		DX11RenderingApi(GLFWwindow* window);
		~DX11RenderingApi();
		inline static ID3D11Device* GetDevice() { return m_Device; }
		inline static ID3D11DeviceContext* GetContext() { return m_Context; }
		inline static IDXGISwapChain* GetSwapChain() { return m_SwapChain; }

		inline static ID3D10Blob* GetVSCode() { return m_VSCode; }
		inline static void SetVSCode(ID3D10Blob* vscode) { m_VSCode = vscode; }

		inline static ID3D10Blob* GetPSCode() { return m_PSCode; }
		inline static void SetPSCode(ID3D10Blob* pscode) { m_PSCode = pscode; }
		static void Clear();

		virtual void Init(GLFWwindow* window) override;
		virtual void ShutDown() override;

	private:
		void InitD3D(GLFWwindow* window);
		void InitStates();
	
	private:
		static ID3D11Device* m_Device;
		static ID3D11DeviceContext* m_Context;
		static IDXGISwapChain* m_SwapChain;
		static ID3D11RenderTargetView* m_BackBuffer;
		static ID3D11RasterizerState* m_RS;
		static ID3D11SamplerState* m_SS;
		static ID3D11BlendState* m_BS;
		static ID3D11DepthStencilView* m_Zbuffer;
		static ID3D10Blob* m_VSCode;
		static ID3D10Blob* m_PSCode;
	};

	
}