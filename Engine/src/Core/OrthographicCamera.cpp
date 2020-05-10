#include "OrthographicCamera.h"


namespace Engine {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
	{
		m_Projection = glm::ortho(left, right, bottom, top, near, far);
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top, float near, float far)
	{
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

	void OrthographicCamera::RecalculateView()
	{
		m_View = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_View = glm::inverse(m_View);
	}

}