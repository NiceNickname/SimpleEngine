#include "pch.h"

#include "Camera.h"
#include "GLFW/glfw3.h"
#include "Input/Input.h"



namespace Engine {

#define PI 3.14159f

	Camera::Camera(const glm::mat4& ProjectionMatrix)
		: m_ProjectionMatrix(ProjectionMatrix)
	{
		m_PanSpeed = 0.0015f;
		m_RotationSpeed = 0.002f;
		m_ZoomSpeed = 0.2f;
		    
		m_Position = { 0, 0, 2 };
		m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

		m_FocalPoint = glm::vec3(0.0f);
		m_Distance = glm::distance(m_Position, m_FocalPoint);

		m_Yaw = 0.0f;
		m_Pitch = 0.0f;
	}

	void Camera::Update()
	{
		const glm::vec2& mouse{ Input::MousePosition().first, Input::MousePosition().second };
		glm::vec2 delta = mouse - m_InitialMousePosition;
		m_InitialMousePosition = mouse;

		if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			MouseRotate(delta);
		else if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
			MousePan(delta);	
		else if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
			MouseZoom(delta.y);


		if (Input::IsKeyDown(GLFW_KEY_W))
			MousePan({ 0.0f, 10.0f });
		if (Input::IsKeyDown(GLFW_KEY_A))
			MousePan({ 10.0f, 0.0f });
		if (Input::IsKeyDown(GLFW_KEY_S))
			MousePan({ 0.0f, -10.0f });
		if (Input::IsKeyDown(GLFW_KEY_D))
			MousePan({ -10.0f, 0.0f });
		m_Position = CalculatePosition();

		glm::quat orientation = GetOrientation();

		m_Rotation = glm::eulerAngles(orientation) * (180.0f / (float)PI);
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 1)) * 
			glm::toMat4(glm::conjugate(orientation)) * 
			glm::translate(glm::mat4(1.0f), -m_Position);
	}

	glm::vec3 Camera::GetUpDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 Camera::GetRightDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 Camera::GetForwardDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	void Camera::MousePan(const glm::vec2& delta)
	{
		m_FocalPoint += -GetRightDirection() * delta.x * m_PanSpeed * m_Distance;
		m_FocalPoint += GetUpDirection() * delta.y * m_PanSpeed * m_Distance;
	}

	void Camera::MouseRotate(const glm::vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * m_RotationSpeed;
		m_Pitch += delta.y * m_RotationSpeed;
	}

	void Camera::MouseZoom(float delta)
	{
		m_Distance -= delta * m_ZoomSpeed;
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}

	glm::vec3 Camera::CalculatePosition()
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	glm::quat Camera::GetOrientation()
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}

}