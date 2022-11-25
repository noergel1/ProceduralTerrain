#pragma once

#include "ProjectionMatrix.h"

namespace Vuse
{
	// Default camera values
	const glm::vec3 UP_DEFAULT = glm::vec3( 0.0f, 1.0f, 0.0f );
	const float YAW_DEFAULT = -90.0f;
	const float PITCH_DEFAULT = 0.0f;
	const float SPEED_DEFAULT = 2.5f;
	const float ACCELERATION_FACTOR = 3.0f;
	const float SENSITIVITY_DEFAULT = 0.1f;

	class Camera
	{
	public:
		Camera( ProjectionMatrix& projectionMatrix, glm::vec3 position, float yaw = YAW_DEFAULT, float pitch = PITCH_DEFAULT, glm::vec3 up = UP_DEFAULT);
		~Camera();

		void Update();

		inline glm::vec3 GetPosition() { return m_Position; }
		inline void SetPosition( glm::vec3 value ) { m_Position = value; }

		inline float GetYaw() { return m_Yaw; }
		inline void SetYaw( float value ) { m_Yaw = value; }

		inline float GetPitch() { return m_Pitch; }
		inline void SetPitch( float value ) { m_Pitch = value; }

		glm::vec3 GetViewDirection();
		glm::vec3 GetRightVector();

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewProjectionMatrix();


	private:
		glm::mat4 m_ViewMatrix;
		ProjectionMatrix m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Right;
		glm::vec3 m_Up;
		glm::vec3 m_WorldUp;
		float m_Yaw;
		float m_Pitch;

	};
}