#pragma once
#include <glm/glm.hpp>
#include "glm/gtc/quaternion.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"


namespace Engine {

	class Camera
	{
	public:
		Camera(const glm::mat4& ProjectionMatrix);

		void Update();

		inline float GetDistance() { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

		inline float SetProjectionMatrix(const glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }
		
		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }

		glm::vec3 GetUpDirection();
		glm::vec3 GetRightDirection();
		glm::vec3 GetForwardDirection(); 
		const glm::vec3& GetPosition() { return m_Position; }
		const glm::vec3& GetFocalPoint() { return m_FocalPoint; }
		void MouseZoom(float delta);

	private:
		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);

		glm::vec3 CalculatePosition();
		glm::quat GetOrientation();

	private:
		glm::mat4 m_ProjectionMatrix, m_ViewMatrix;

		glm::vec3 m_Position, m_Rotation, m_FocalPoint;

		glm::vec2 m_InitialMousePosition;
		glm::vec3 m_InitialFocalPoint, m_InitialRotation;

		bool m_Panning, m_Rotating;

		float m_Distance;

		float m_PanSpeed, m_RotationSpeed, m_ZoomSpeed;

		float m_Pitch, m_Yaw;
	};


}