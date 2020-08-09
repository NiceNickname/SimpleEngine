#pragma once

#include "glm/gtc/matrix_transform.hpp"

namespace Engine {

	class OrthographicCamera
	{
	public:

		OrthographicCamera(float AspectRatio);
		~OrthographicCamera() {}

		void SetProjection(float left, float right, float bottom, float top, float near, float far);
		const glm::mat4& GetProjection() { return m_Projection; }

		const glm::mat4& GetView() { return m_View; }
		
		void SetPosition(const glm::vec3& position);
		const glm::vec3& GetPosition() { return m_Position; }

		void SetRotation(float rotation);
		float GetRotation() { return m_Rotation; }

		float GetSpeed() { return m_TranslationSpeed; }
		void SetSpeed(float speed) { m_TranslationSpeed = speed; }

		void Zoom(float ZoomLevel);

	private:
		void RecalculateView();

	private:
		glm::mat4 m_View;
		glm::mat4 m_Projection;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

		float m_TranslationSpeed = 0.05f;
		float m_Rotation = 0.0f;

		float m_Zoom = 1.0f;

		float m_AspectRatio = 16.0f / 9.0f;
	};
}