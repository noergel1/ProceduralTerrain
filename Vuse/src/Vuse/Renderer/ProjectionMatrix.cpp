#include "vuse_pch.h"
#include "ProjectionMatrix.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace Vuse
{
	ProjectionMatrix::ProjectionMatrix( float fov, float aspectRatio, float nearPlane, float farPlane )
		:m_FOV(fov)
		,m_AspectRatio(aspectRatio)
		,m_NearPlane(nearPlane)
		,m_FarPlane(farPlane)
	{
		CalcMatrix();
	}

	glm::mat4 ProjectionMatrix::Get()
	{
		return m_ProjectionMatrix;
	}

	float ProjectionMatrix::GetFOV()
	{
		return m_FOV;
	}

	void ProjectionMatrix::SetFOV( float value )
	{
		m_FOV = value;
		CalcMatrix();
	}

	float ProjectionMatrix::GetAspectRatio()
	{
		return m_AspectRatio;
	}

	void ProjectionMatrix::SetAspectRatio( float value )
	{
		m_AspectRatio = value;
		CalcMatrix();
	}

	float ProjectionMatrix::GetNearPlane()
	{
		return m_NearPlane;
	}

	void ProjectionMatrix::SetNearPlane( float value )
	{
		m_NearPlane = value;
		CalcMatrix();
	}

	float ProjectionMatrix::GetFarPlane()
	{
		return m_FarPlane;
	}

	void ProjectionMatrix::SetFarPlane( float value )
	{
		m_FarPlane = value;
		CalcMatrix();
	}

	void ProjectionMatrix::CalcMatrix()
	{
		m_ProjectionMatrix = glm::perspective( m_FOV, m_AspectRatio, m_NearPlane, m_FarPlane );
	}
}