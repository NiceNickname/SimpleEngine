#pragma once
#include <memory>
#include "Window/Window.h"


namespace Engine
{
	class App
	{
	public:
		App() {}
		virtual void Run();

	protected:

		std::unique_ptr<Window> m_Window;

		bool m_Running = true;

	};
}

