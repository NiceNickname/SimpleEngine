#pragma once

#include "Window/Window.h"

namespace Engine {
	class RenderingAPI
	{
	public:
		static RenderingAPI* Create(const std::unique_ptr<Window>& window);
		virtual ~RenderingAPI() = default;
		virtual void ShutDown() = 0;
		virtual void SwapBuffers() = 0;
		virtual void Prepare() {};
		virtual void ClearBuffer() = 0;
	};
}