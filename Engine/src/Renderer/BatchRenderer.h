#pragma once

#include <glm/glm.hpp>
#include "Texture.h"

namespace Engine {

	class BatchRenderer
	{
	public:

		static BatchRenderer* Create();

		virtual ~BatchRenderer() = default;

		virtual void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) = 0;
		virtual void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture) {}
		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void Draw() = 0;

	};

}