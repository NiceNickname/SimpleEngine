#pragma once
#include "Renderer/RenderingAPI.h"
#include "Window/Win32Window.h"

#include <d3d11.h>
#include <d3dcompiler.h>



namespace Engine {

	// TODO: move compiled shader code to shader class

	class DX11RenderingApi  : public RenderingAPI 
	{

	public:
		DX11RenderingApi(const std::unique_ptr<Window>& window);
		~DX11RenderingApi();

		inline static ID3D11Device* GetDevice() { return m_Device; }
		inline static ID3D11DeviceContext* GetContext() { return m_Context; }
		inline static IDXGISwapChain* GetSwapChain() { return m_SwapChain; }
		inline static ID3D11RenderTargetView* GetBackBuffer() { return m_BackBuffer;  }
		static void ClearBuffer();
		virtual void Render() override;

		virtual void ShutDown() override;

		virtual void SwapBuffers() override;

		

	private:
		void InitD3D(HWND hwnd);
		void InitStates();
	
	private:
		static ID3D11Device* m_Device;
		static ID3D11DeviceContext* m_Context;
		static IDXGISwapChain* m_SwapChain;
		static ID3D11RenderTargetView* m_BackBuffer;
		static ID3D11RasterizerState* m_RS;
		static ID3D11SamplerState* m_SS;
		static ID3D11BlendState* m_BS;

		static HWND hwnd;
	};

	
}