#pragma once
#include <memory>
#include "Window/Window.h"


namespace Engine
{
	class App
	{
	public:
		App() { m_Window = std::make_unique<Engine::Window>(); }
		virtual ~App() {}

		void Run();

	protected:
		virtual void Start() {}
		virtual void Update() {}
		virtual void Render() {}

	protected:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;


	};
}

