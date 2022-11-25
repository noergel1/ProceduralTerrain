#include "vuse_pch.h"
#include "Camera.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace Vuse
{
	Camera::Camera( ProjectionMatrix& projectionMatrix, glm::vec3 position, float yaw, float pitch, glm::vec3 up )
		:m_ProjectionMatrix(projectionMatrix)
		,m_Position(position)
		,m_Yaw(yaw)
		,m_Pitch(pitch)
		,m_WorldUp(up)
	{
		Update();
	}

	Camera::~Camera()
	{
	}

	void Camera::Update()
	{
		// calculate the new Front vector
		m_Front.x = cos( glm::radians( m_Yaw ) ) * cos( glm::radians( m_Pitch ) );
		m_Front.y = sin( glm::radians( m_Pitch ) );
		m_Front.z = sin( glm::radians( m_Yaw ) ) * cos( glm::radians( m_Pitch ) );
		// also re-calculate the Right and Up vector
		m_Right = glm::normalize( glm::cross( m_Front, m_WorldUp ) );  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_Up = glm::normalize( glm::cross( m_Right, m_Front ) );
	}

	glm::vec3 Camera::GetViewDirection()
	{
		Update();
		return m_Front; 
	}

	glm::vec3 Camera::GetRightVector()
	{
		Update();
		return m_Right;
	}

	glm::mat4 Camera::GetViewMatrix() {
		Update();
		m_ViewMatrix = glm::lookAt( m_Position, m_Position + m_Front, m_Up );
		return m_ViewMatrix; 
	}

	glm::mat4 Camera::GetProjectionMatrix() { 
		return m_ProjectionMatrix.Get(); 
	}

	glm::mat4 Camera::GetViewProjectionMatrix() { 
		m_ViewProjectionMatrix = m_ProjectionMatrix.Get() * GetViewMatrix();
		return m_ViewProjectionMatrix; 
	}
}