#pragma once

#include <glm/glm.hpp>

namespace Vuse
{
	class ProjectionMatrix
	{
	public:
		ProjectionMatrix( float fov, float aspectRatio, float nearPlane, float farPlane );

		glm::mat4 Get();

		float GetFOV();
		void SetFOV( float value );

		float GetAspectRatio();
		void SetAspectRatio( float value );

		float GetNearPlane();
		void SetNearPlane( float value );

		float GetFarPlane();
		void SetFarPlane( float value );

	private:
		void CalcMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;

		float m_FOV;
		float m_AspectRatio;
		float m_NearPlane;
		float m_FarPlane;
	};
}