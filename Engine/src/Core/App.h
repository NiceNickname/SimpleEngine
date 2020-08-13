#pragma once

#include "Renderer/Renderer2D.h"

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
		Renderer2D::API m_Api = Renderer2D::API::NONE;
	};
}

