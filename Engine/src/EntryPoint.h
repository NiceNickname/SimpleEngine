#pragma once
#include <stdlib.h>
#include <crtdbg.h>
#include "Core/App.h"
#include "Core/Log.h"


	Engine::App* CreateApp();

	int main(void)
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		Engine::Log::Init();

		auto app = CreateApp();

		app->Run();

		delete app;

		return 0;
	}
