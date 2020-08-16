#pragma once
#include "Renderer/RenderingAPI.h"
#include "Window/Win32Window.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include "glm/glm.hpp"


namespace Engine {

	class DX11RenderingApi  : public RenderingAPI 
	{

	public:
		DX11RenderingApi(const std::unique_ptr<Window>& window);
		~DX11RenderingApi();

		inline static ID3D11Device* GetDevice() { return s_Device; }
		inline static ID3D11DeviceContext* GetContext() { return s_Context; }
		inline static IDXGISwapChain* GetSwapChain() { return s_SwapChain; }
		inline static ID3D11RenderTargetView* GetBackBuffer() { return s_BackBuffer;  }
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void ClearBuffer() override;
		virtual void SetVSync(bool enabled);
		
		// setting render target each frame
		virtual void Prepare() override;

		virtual void ShutDown() override;

		virtual void SwapBuffers() override;

		

	private:
		void InitD3D(HWND hwnd);
		void InitStates();
	
	private:
		static ID3D11Device* s_Device;
		static ID3D11DeviceContext* s_Context;
		static IDXGISwapChain* s_SwapChain;
		static ID3D11RenderTargetView* s_BackBuffer;
		static ID3D11RasterizerState* s_RS;
		static ID3D11SamplerState* s_SS;
		static ID3D11BlendState* s_BS;
		static ID3D11DepthStencilView* s_ZBuffer;
		static HWND s_Hwnd;
		static unsigned int s_ScreenWidth;
		static unsigned int s_ScreenHeight;
		static unsigned int s_Numerator;
		static unsigned int s_Denominator;
		static bool s_VSyncEnabled;
		static glm::vec4 s_ClearColor;
		
	};

	
}