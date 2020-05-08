#include "App.h"

namespace Engine
{
	void App::Run()
	{
		Start();

		while (m_Running)
		{
			Update();
			Render();
			m_Window->Update();

			if (glfwWindowShouldClose(m_Window->GetPointer()))
				m_Running = false;
		}
	}
}
