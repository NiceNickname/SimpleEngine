#pragma once

#include "glm/gtc/matrix_transform.hpp"

namespace Engine {

	class OrthographicCamera
	{
	public:

		OrthographicCamera(float left, float right, float bottom, float top, float near, float far);
		~OrthographicCamera() {}

		void SetProjection(float left, float right, float bottom, float top, float near, float far);
		const glm::mat4& GetProjection() { return m_Projection; }

		const glm::mat4& GetView() { return m_View; }
		
		void SetPosition(const glm::vec3& position);
		const glm::vec3& GetPosition() { return m_Position; }

		void SetRotation(float rotation);
		float GetRotation() { return m_Rotation; }

	private:
		void RecalculateView();

	private:
		glm::mat4 m_View;
		glm::mat4 m_Projection;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}