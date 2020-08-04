#pragma once
#include "Renderer/RenderingAPI.h"

#include <d3d11.h>
#include <d3dcompiler.h>



namespace Engine {

	// TODO: move compiled shader code to shader class

	class DX11RenderingApi  : public RenderingAPI 
	{

	public:
		DX11RenderingApi(GLFWwindow* window);
		~DX11RenderingApi();

		inline static ID3D11Device* GetDevice() { return m_Device; }
		inline static ID3D11DeviceContext* GetContext() { return m_Context; }
		inline static IDXGISwapChain* GetSwapChain() { return m_SwapChain; }

		static void ClearBuffer();

		virtual void Init(GLFWwindow* window) override;
		virtual void ShutDown() override;

		static void SwapBuffers(unsigned int SyncInterval, unsigned int Flags);

		

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
	};

	
}