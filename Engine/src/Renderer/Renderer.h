#pragma once
#include "Engine.h"
namespace Engine {

	class Renderer
	{
	public:
		static void Init();
		static void Begin();
		static void End();
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture);
		static void Flush();
		static void ShutDown();
		static void Draw();

	private:


	};

}