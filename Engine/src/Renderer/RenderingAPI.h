#pragma once

#include "Window/Window.h"
#include "glm/glm.hpp"


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
		virtual void SetVSync(bool enabled) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
	};
}