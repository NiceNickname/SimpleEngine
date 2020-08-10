#include "pch.h"

#include "OrthographicCamera.h"
#include <algorithm>
#include "Input/Input.h"


namespace Engine {

	OrthographicCamera::OrthographicCamera(float AspectRatio)
	{
		m_AspectRatio = AspectRatio;
		m_Projection = glm::ortho(-AspectRatio, AspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top, float near, float far)
	{
		m_AspectRatio = (right - left) / (top - bottom);

		m_Projection = glm::ortho(left, right, bottom, top, near, far);
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateView();
	}


	void OrthographicCamera::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		RecalculateView();
	}

	void OrthographicCamera::Zoom(float ZoomLevel)
	{
		if (ZoomLevel == 0)
			return;

		m_Zoom -= ZoomLevel;
		m_Zoom = std::max(0.25f, m_Zoom);
		Input::MouseScrolled(0);
		SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom, -1.0f, 1.0f);
	}

	void OrthographicCamera::RecalculateView()
	{
		m_View = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_View = glm::inverse(m_View);
	}

}