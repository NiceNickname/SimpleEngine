#pragma once

#include "Renderer/Renderer.h"

namespace Engine
{
	class App
	{
	public:
		App() = default;
		virtual ~App() = default;

		void Run();
		void ImGuiBegin();
		void ImGuiEnd();
		void ShutDown();

	protected:
		virtual void Start() {}
		virtual void Update() {}
		virtual void Render() {}
		virtual void ImGuiRender() {}
		virtual void ChooseApi() {}
		

	protected:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		Renderer::API m_Api = Renderer::API::NONE;
	};
}

