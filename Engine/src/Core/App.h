#pragma once

#include "Window/GlfwWindow.h"
#include "Renderer/Renderer.h"

namespace Engine
{
	class App
	{
	public:
		App() { Renderer::SetApi(m_Api, m_Window); }
		virtual ~App() {}

		void Run();
		void ImGuiBegin();
		void ImGuiEnd();

	protected:
		virtual void Start() {}
		virtual void Update() {}
		virtual void Render() {}
		virtual void ImGuiRender() {}

	protected:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		Renderer::API m_Api = Renderer::API::DX11;
	};
}

