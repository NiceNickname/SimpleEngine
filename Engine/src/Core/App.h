#pragma once

#include "Window/Window.h"



class App
{
public:
	App() {}
	virtual void Run();

protected:

	Window* m_Window;

	bool m_Running = true;

};

